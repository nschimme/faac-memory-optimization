#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "faac.h"

int main()
{
    int i;
    faacEncHandle hEncoder;
    uint64_t inputSamples = 0;
    uint64_t maxOutputBytes = 0;
    int32_t enc_out_len = 0;
    int32_t read_len = 0;
    FILE *fpr;
    FILE *fpw;
    uint8_t *in_buf;
    uint8_t *out_buf;

    fpr = fopen("in.pcm", "rb");
    if (fpr == NULL)
    {
        printf("open input file error\n");
        goto exit1;
    }

    fpw = fopen("out.aac", "wb");
    if (fpw == NULL)
    {
        printf("open output file error\n");
        goto exit2;
    }

    hEncoder = faacEncOpen(44100, 2, &inputSamples, &maxOutputBytes);

    in_buf = (uint8_t *)malloc(sizeof(int16_t) * inputSamples);
    if (in_buf == NULL)
    {
        printf("malloc in_buf error\n");
        goto exit3;
    }

    out_buf = (uint8_t *)malloc(maxOutputBytes);
    if (out_buf == NULL)
    {
        printf("malloc out_buf error\n");
        goto exit4;
    }

    printf("in_buf size %d, out_buf size %d\n", (int32_t)(sizeof(int16_t) * inputSamples), (int32_t)maxOutputBytes);

    faacEncConfigurationPtr config = faacEncGetCurrentConfiguration(hEncoder);

    config->mpegVersion = MPEG4;
    config->aacObjectType = LOW;
    // config->jointmode = JOINT_NONE;
    // config->useLfe = 0;
    // config->useTns = 0;
    config->bitRate = 128000;
    config->bandWidth = 16000;
    // config->quantqual = 0;
    config->outputFormat = ADTS_STREAM;
    config->inputFormat = FAAC_INPUT_16BIT;
    // config->pnslevel = 0;

    if (!faacEncSetConfiguration(hEncoder, config))
    {
        printf("unsupported output format!\n");
        goto exit5;
    }

    printf("---- start ----\n");

    i = 0;
    while (i++ < 1000)
    {
        read_len = fread(in_buf, 1, sizeof(int16_t) * inputSamples, fpr);
        if (read_len != sizeof(int16_t) * inputSamples)
        {
            fseek(fpr, 0, SEEK_SET);
            continue;
        }
        enc_out_len = faacEncEncode(hEncoder, (int32_t *)in_buf, inputSamples, out_buf, maxOutputBytes);
        fwrite(out_buf, 1, enc_out_len, fpw);
    }

    faacEncClose(hEncoder);

    printf("---- finish ----\n");

exit5:
    free(out_buf);
exit4:
    free(in_buf);
exit3:
    fclose(fpw);
exit2:
    fclose(fpr);
exit1:

    return 0;
}
