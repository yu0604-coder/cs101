#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int n;
    scanf("%d", &n);   // 輸入組數 1~5

    // 讀取目前銷售編號（放在 counter.bin）
    FILE *fp_cnt = fopen("counter.bin", "rb");
    int counter = 0;

    if (fp_cnt != NULL) {
        fread(&counter, sizeof(int), 1, fp_cnt);
        fclose(fp_cnt);
    }

    counter++;  // 本次銷售編號 +1

    // 存回 counter.bin
    fp_cnt = fopen("counter.bin", "wb");
    fwrite(&counter, sizeof(int), 1, fp_cnt);
    fclose(fp_cnt);

    // 建立檔名 lotto00001.txt
    char filename[64];
    sprintf(filename, "lotto%05d.txt", counter);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Failed to create file.\n");
        return 1;
    }

    // 取得系統時間
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char time_str[64];
    strftime(time_str, sizeof(time_str), "%a %b %e %T %Y", t);

    // 標頭
    fprintf(fp, "========= lotto649 =========\n");
    fprintf(fp, "======== No.%05d =========\n", counter);
    fprintf(fp, "%s\n", time_str);

    srand((unsigned) time(NULL));

    for (int i = 1; i <= 5; i++) {
        fprintf(fp, "[%d]: ", i);

        if (i <= n) {
            int nums[7];
            int used[70] = {0};

            for (int k = 0; k < 7; k++) {
                int r = rand() % 69 + 1;
                while (used[r]) {
                    r = rand() % 69 + 1;
                }
                used[r] = 1;
                nums[k] = r;
            }

            for (int k = 0; k < 7; k++) {
                fprintf(fp, "%02d ", nums[k]);
            }
            fprintf(fp, "\n");
        } else {
            fprintf(fp, "__ __ __ __ __ __ __\n");
        }
    }

    fprintf(fp, "========= csie@CGU =========\n");

    fclose(fp);

    return 0;
}
