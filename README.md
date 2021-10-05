# ˵��
faac�ڴ濪���ϴ�Ϊ����Ƕ��ʽ�豸ʹ�ý����Ż�����github������issues����û�����ң����Ծ͸�һ�ݴ����Լ���ɡ�
����faac_1_30�汾��ԭ���� https://github.com/knik0/faac

# �ļ�˵��
* faac-1_30.zip Ϊ faac Դ��
* Ϊ�˷����Ҹ���ʹ�ã�ɾ���� faac Դ�������ò������ļ���ֻ���� libfaac Ŀ¼�µı�Ҫ�ļ��� inlcude Ŀ¼
* ���� CMakeLists.txt ����ű�

# �ڴ��Ż�������
�ڴ��Ż������ļ��ĸ�ʽΪ PCM int16 С�� ˫���� 44100Hz

## 1.1 �Ż�ǰ
ʹ�� valgrind ����ڴ棬������£����Կ���Ĭ�����õ��ڴ濪��ԼΪ 11.5 MB
![](./doc/img/mem01.png)

## 1.2 �޸�Ĭ�����������
�޸� libfaac\coder.h
һ����˵��˫�����͹����ˣ������5.1����֮�������������������޸�

�޸�ǰ
`#define MAX_CHANNELS 64`
�޸ĺ�
`#define MAX_CHANNELS 2`

�ڴ�ͳ�����£�Լ 560 KB
![](./doc/img/mem02.png)

## 1.3 ɾ�� bwpInfo
�޸� libfaac\coder.h
�� faacEncOpen() �лᴴ�� faacEncStruct* hEncoder; ������
�� faacEncStruct.coderInfo �е� bwpInfo ������û���õ�����֪������Ϊʲôû��ɾ�������岻����

�޸�ǰ
`BwpInfo bwpInfo;`
�޸ĺ�
`// BwpInfo bwpInfo;`

�ڴ�ͳ�����£�Լ 240 KB
![](./doc/img/mem03.png)

## 1.4 ɾ����Ч����
�޸� libfaac\frame.c
faacEncEncode() �Ĵ�����������һ��
```
hEncoder->sampleBuff[channel]		= hEncoder->nextSampleBuff[channel];
hEncoder->nextSampleBuff[channel]	= hEncoder->next2SampleBuff[channel];
hEncoder->next2SampleBuff[channel]	= hEncoder->next3SampleBuff[channel];
hEncoder->next3SampleBuff[channel]	= tmp;
```
������4��sampleBuff���������ÿ����һ�λ����ν�����4��buffer��ʵ�ʴ�����ֻ�õ��� sampleBuff �� next3SampleBuff������������Ϊʲô����д��Ҳ����������ɾ����������޸�Ϊ
```
hEncoder->sampleBuff[channel]		= hEncoder->next3SampleBuff[channel];
hEncoder->next3SampleBuff[channel]	= tmp;
```

���¼����ǵ�ҲҪһ���޸�

faacEncOpen() ���޸�Ϊ
```
// hEncoder->nextSampleBuff[channel] = NULL;
// hEncoder->next2SampleBuff[channel] = NULL;
```

faacEncClose() ���޸�Ϊ
```
// if (hEncoder->nextSampleBuff[channel])
//   FreeMemory(hEncoder->nextSampleBuff[channel]);
// if (hEncoder->next2SampleBuff[channel])
//   FreeMemory (hEncoder->next2SampleBuff[channel]);
```

faacEncStruct ���޸�Ϊ
```
// double *nextSampleBuff[MAX_CHANNELS];
// double *next2SampleBuff[MAX_CHANNELS];
```

����ÿ�������Խ�Լ 16KB �ڴ�

�ڴ�ͳ�����£�Լ 210 KB
![](./doc/img/mem04.png)

## 1.5 �Ż����ݽṹ
�޸� libfaac\coder.h
���и�ǰ�����������ǲ����� DRM��������� libfaac\coder.h��Ĭ�Ͼ��ǹرյ�
```//#define DRM```

�������ٿ����룬CoderInfo ��������һ����Ա
```
struct {
    int data;
    int len;
} s[DATASIZE];
```
���������й��������룬�鿴Դ���֪������ṹ��ֻ�� huffcode() �����и�ֵ����������������ڹ����������ʹ�õ����Ϊ book01 �� book11��û���õ�book12����11�����ĳ�Աԭ������
```
typedef struct {
    const uint16_t len;
    const uint16_t data;
} hcode16_t;
```
��˿��԰�int�ĳ�short��ÿ�������Խ�Լ6KB�ڴ�

�ڴ�ͳ�����£�Լ 200 KB
![](./doc/img/mem05.png)

## 1.6 ���� TNS
�޸� libfaac\coder.h libfaac\bitstream.c
����޸Ļ�Ӱ�����ʣ�ʵ��Ӱ���С�������ϵĲ���Ҫ��ϸ�����ܲ����������Ϊ��һ�������ϵ���ʧ��ȫ���Խ��ܡ�
�� CoderInfo.tnsInfo ��ԱҲȥ������ɾ�� faacEncEncode() �� TnsEncode() �ĵ����Լ����� TnsInit() ���á�
ɾ�� faacEncConfiguration �е� unsigned int useTns
����ʱɾ�� tns.c
ֱ�ӽ� WriteTNSData() �����޸�����
```
static int WriteTNSData(CoderInfo *coderInfo,
                        BitStream *bitStream,
                        int writeFlag)
{
    int bits = 0;

#ifndef DRM
    if (writeFlag) {
        PutBit(bitStream, 0, LEN_TNS_PRES);
    }
    bits += LEN_TNS_PRES;
#endif

    return bits;
}
```

�ڴ�ͳ�����£�Լ 170 KB
![](./doc/img/mem06.png)

## 1.7 �޸���������
�޸������ļ��� double Ϊ float
��������˵����޸Ļ�Ӱ�����ʣ�ʵ��û��������������Ϊ����޸�Ӧ��û����
ÿ�����ڴ��ٽ�ʡһ��

�ڴ�ͳ�����£���Լ 90 KB
![](./doc/img/mem07.png)

## 1.8 ����
�����޹ؽ�Ҫ�����Ż�һ��㣬����Ͳ�ͳ����
faacEncConfiguration �� int channel_map[64]; ���Ը�Ϊ int channel_map[MAX_CHANNELS];
faacEncStruct ȥ�� double *msSpectrum[MAX_CHANNELS];

# �Ż��ܽ�
��ȥ main() �����������buffer�����������Ż��Ѿ���������������Լ 70 KB��˫����Լ 90 KB���������ڴ濪����ʹ�ŵ�stm32�Ĳ����и߶��ͺ��϶������У���Ҫɶ���г���

�������ڴ�ͳ�����£���Լ 70 KB
![](./doc/img/mem07.png)

�������и��õ��Ż�������ӭ���Է���

# ��������
Q: windows���뱨�� #include "win32_ver.h"
A: ����ļ�����configure���ɵģ�Ŀǰ���ƺ�û��̫��Ӱ�죬��ȥ��
