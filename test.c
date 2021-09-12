#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "faac.h"

FILE *fpr;
FILE *fpw;

uint8_t in_buf[4096];
int16_t in_buf16[4096];
int32_t in_buf32[4096];
uint8_t out_buf[8192];

int main()
{
    int i;
    faacEncHandle hEncoder;
    uint64_t inputSamples = 0;
    uint64_t maxOutputBytes = 0;
    int32_t enc_out_len = 0;

    printf("\n---- start ----\n");

    fpr = fopen("in.pcm", "rb");
    fpw = fopen("out.aac", "wb");

    hEncoder = faacEncOpen(44100, 2, &inputSamples, &maxOutputBytes);

    faacEncConfigurationPtr config = faacEncGetCurrentConfiguration(hEncoder);

    config->mpegVersion = MPEG4;
    config->aacObjectType = LOW;
    // config->jointmode = JOINT_NONE;
    // config->useLfe = 0;
    // config->useTns = 0;
    config->bitRate = 64000;
    config->bandWidth = 16000;
    // config->quantqual = 0;
    config->outputFormat = ADTS_STREAM;
    config->inputFormat = FAAC_INPUT_16BIT;
    // config->pnslevel = 0;

    if (!faacEncSetConfiguration(hEncoder, config))
    {
        fprintf(stderr, "Unsupported output format!\n");
        return 1;
    }

    i = 0;
    while (i++ < 1000)
    {
        fread(in_buf16, 2, 2048, fpr);
        enc_out_len = faacEncEncode(hEncoder, in_buf16, inputSamples, out_buf, maxOutputBytes);
        fwrite(out_buf, 1, enc_out_len, fpw);
    }

    faacEncClose(hEncoder);

    fclose(fpr);
    fclose(fpw);

    printf("\n---- finish ----\n");

    return 0;
}

