#include <stdio.h>

int main(){
    int max = -1;
    int value;

    printf("input value: ");
    scanf("%d",&value);
    for (;value >= 0;){
        printf("input value: ");
        scanf("%d",&value);
        if (max < value){
            max = value;
        }
        if (value <= -1){
            break;
        }
    }
    printf("最大値: %d\n",max);

return 0;
}