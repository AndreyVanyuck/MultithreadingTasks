//4)    F[i]=A[i]-B[i]*C[i]-D[i] , i=1...8;

#include <iostream>

#define SIZE 8


void convert_b_to_w(__int8* arr, __int16* res) {
    __asm
    {
        mov eax, res;
        mov ebx, arr;
        movq mm0, [ebx];
        movq mm1, [ebx];
        pxor mm2, mm2;
        punpckhbw mm0, mm2;
        punpcklbw mm1, mm2;
        movq[eax + 8], mm0;
        movq[eax], mm1;
    }
}


void sub_w(__int16* op1, __int16* op2, __int16* res) {
    for (int i = 0; i < SIZE / 4; i++) {
        int j = i * 8;
        __asm
        {
            mov eax, res;
            mov ebx, op1;
            mov ecx, op2;
            mov edx, j;
            movq mm0, [ebx + edx];
            movq mm1, [ecx + edx];
            psubw mm0, mm1;
            movq[eax + edx], mm0;
        }
    }
}

void mul_w(__int16* op1, __int16* op2, __int16* res) {
    for (int i = 0; i < SIZE / 4; i++) {       
        int j = i * 8;
        __asm
        {
            mov eax, res;
            mov ebx, op1;
            mov ecx, op2;
            mov edx, j;
            movq mm0, [ebx + edx];
            movq mm1, [ecx + edx];
            pmullw mm0, mm1;
            movq[eax + edx], mm0;
        }
    }
}

int main()
{
    __int8 A[SIZE] = { 1,2,3,4,5,6,7,8 };
    __int8 B[SIZE] =  { 9,10,11,12,13,14,15,16 };
    __int8 C[SIZE] = { 17,18,19,20,21,22,23,24 };
    __int16 D[SIZE] = { 25,26,27,28,29,30,31,32 };

    __int16 A_w[SIZE];
    __int16 B_w[SIZE];
    __int16 C_w[SIZE];
    __int16 mul_res[SIZE];
    __int16 sub_res[SIZE];
    __int16 res[SIZE];

    printf("Expected result: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", A[i] - B[i] * C[i] - D[i]);
    }
    std::cout << std::endl;

    convert_b_to_w(A, A_w);
    convert_b_to_w(B, B_w);
    convert_b_to_w(C, C_w);
                                          
    mul_w(B_w, C_w, mul_res);
    sub_w(A_w, mul_res, sub_res);
    sub_w(sub_res, D, res);
    
    printf("Result: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", res[i]);
    }
    std::cout << std::endl;

    return 0;
}