#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/geo.h"
#include "../include/qry.h"
#include "../include/svg.h"
#include "../include/txt.h"
#include "../include/via.h"

#define PATH_LEN 512
#define FILE_NAME_LEN 256

void monta_caminho(char* destino, size_t tamanho_max, const char* dir, const char* arquivo) {
    if (strlen(dir) > 0) {
        if (dir[strlen(dir) - 1] == '/') {
            snprintf(destino, tamanho_max, "../%s%s", dir, arquivo);
        } else {
            snprintf(destino, tamanho_max, "../%s/%s", dir, arquivo);
        }
    } else {
        snprintf(destino, tamanho_max, "../%s", arquivo);
    }
}

int main(int argc, char* argv[]) {
    char dirEntrada[PATH_LEN] = "";
    char dirSaida[PATH_LEN] = "";
    char nomeArquivoGeo[FILE_NAME_LEN] = "";
    char nomeArquivoQry[FILE_NAME_LEN] = "";
    char nomeArquivoVia[FILE_NAME_LEN] = "";
    char onlyQry[FILE_NAME_LEN] = "";
    char baseQry[FILE_NAME_LEN] = "";
    char baseGeo[FILE_NAME_LEN] = "";
    char baseVia[FILE_NAME_LEN] = "";
    int hasEntrada = 0, hasQry = 0, hasVia = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            strcpy(dirEntrada, argv[++i]);
            hasEntrada = 1;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            strcpy(dirSaida, argv[++i]);
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoGeo, argv[++i]);
            char *pNome = strrchr(nomeArquivoGeo, '/');
            strcpy(baseGeo, pNome ? pNome + 1 : nomeArquivoGeo);
            char *pExt = strrchr(baseGeo, '.');
            if (pExt && strcmp(pExt, ".geo") == 0) {
                *pExt = '\0';
            }
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoQry, argv[++i]);
            char *p = strrchr(argv[i], '/');
            strcpy(onlyQry, p ? p + 1 : argv[i]);
            char *pNome = strrchr(nomeArquivoQry, '/');
            strcpy(baseQry, pNome ? pNome + 1 : nomeArquivoQry);
            char *pExt = strrchr(baseQry, '.');
            if (pExt && strcmp(pExt, ".qry") == 0) {
                *pExt = '\0';
            }
            hasQry = 1;
        } else if (strcmp(argv[i], "-v") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoVia, argv[++i]);
            char *pNome = strrchr(nomeArquivoVia, '/');
            strcpy(baseVia, pNome ? pNome + 1 : nomeArquivoVia);
            char *pExt = strrchr(baseVia, '.');
            if (pExt && strcmp(pExt, ".pm") == 0) {
                *pExt = '\0';
            }
            hasVia = 1;
        } else {
            fprintf(stderr, "Parametro desconhecido ou invalido: %s\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    if (!hasEntrada || !hasQry || !hasVia) {
        fprintf(stderr, "Erro: parametros obrigatorios -e (entrada), -q (qry) e -v (via) nao fornecidos.\n");
        return EXIT_FAILURE;
    }

    char fullPathGeo[1024] = "";
    char fullPathVia[1024] = "";
    char fullPathQry[1024] = "";
    char arquivoSaidaSvgGeo[1024] = "";
    char arquivoSaidaSvgQry[1024] = "";
    char arquivoSaidaTxt[1024] = "";

    monta_caminho(fullPathGeo, sizeof(fullPathGeo), dirEntrada, nomeArquivoGeo);
    monta_caminho(arquivoSaidaSvgGeo, sizeof(arquivoSaidaSvgGeo), dirSaida, baseGeo);
    strcat(arquivoSaidaSvgGeo, ".svg");

    if (strlen(nomeArquivoVia) > 0) {
        monta_caminho(fullPathVia, sizeof(fullPathVia), dirEntrada, nomeArquivoVia);
    }

    if (strlen(nomeArquivoQry) > 0) {
        monta_caminho(fullPathQry, sizeof(fullPathQry), dirEntrada, nomeArquivoQry);
        
        char baseNomeComposto[512];
        snprintf(baseNomeComposto, sizeof(baseNomeComposto), "%s-%s", baseGeo, baseQry);
        
        monta_caminho(arquivoSaidaSvgQry, sizeof(arquivoSaidaSvgQry), dirSaida, baseNomeComposto);
        strcat(arquivoSaidaSvgQry, ".svg");

        monta_caminho(arquivoSaidaTxt, sizeof(arquivoSaidaTxt), dirSaida, baseNomeComposto);
        strcat(arquivoSaidaTxt, ".txt");
    }

    FILE* geo = fopen(fullPathGeo, "r");
    if (!geo) {
        fprintf(stderr, "Falha ao abrir arquivo geo: %s\n", fullPathGeo);
        return EXIT_FAILURE;
    }

    FILE* svgGeo = fopen(arquivoSaidaSvgGeo, "w");
    if (!svgGeo) {
        fprintf(stderr, "Falha ao criar arquivo svg geo: %s\n", arquivoSaidaSvgGeo);
        fclose(geo);
        return EXIT_FAILURE;
    }

    FILE* via = NULL;
    if (strlen(fullPathVia) > 0) {
        via = fopen(fullPathVia, "r");
        if (!via) fprintf(stderr, "Aviso: Nao foi possivel abrir %s\n", fullPathVia);
    }

    FILE* qry = NULL;
    FILE* svgQry = NULL;
    FILE* txt = NULL;
    
    if (strlen(fullPathQry) > 0) {
        qry = fopen(fullPathQry, "r");
        svgQry = fopen(arquivoSaidaSvgQry, "w");
        txt = fopen(arquivoSaidaTxt, "w");
        
        if (!qry || !svgQry || !txt) {
            fprintf(stderr, "Falha ao criar ou abrir arquivos relacionados ao qry.\n");
        }
    }

    Estilo e = criar_estilo("1.0px", "green", "yellow");
    double max_x = 0, max_y = 0;
    int nQuadras = leNumeroQuadras(geo);
    Hashtable htQuadras = criar_hashtable(2*nQuadras);
    Quadra vetQuadra[nQuadras];

    start_svg(svgGeo, max_x, max_y);
    rewind(geo);
    leGeo(geo, htQuadras, svgGeo, vetQuadra, e, &max_x, &max_y);
    fecha_svg(svgGeo);

    Grafo g = leVia(via);

    Registrador vetReg[11] = {NULL};

    if (qry != NULL && svgQry != NULL && txt != NULL) {
        start_svg(svgQry, max_x, max_y);
        leQry(qry, txt, svgQry, g, vetReg, vetQuadra, htQuadras);
        for(int i=0;i<nQuadras;i++){
            insere_quadra_svg(svgQry, vetQuadra[i], e);
        }
        
        fecha_svg(svgQry);
    }

    if (geo) fclose(geo);
    if (svgGeo) fclose(svgGeo);
    if (via) fclose(via);
    if (qry) fclose(qry);
    if (svgQry) fclose(svgQry);
    if (txt) fclose(txt);

    destruir_hashtable(htQuadras);
    for(int i=0;i<nQuadras;i++){
        liberar_quadra(vetQuadra[i]);
    }
    free(e);
    destruir_grafo(g);

    return 0;
}