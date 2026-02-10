void Qsort(int*, int, int);

void Qsort(int* mas, int left, int right)
{
int fix, L_g, R_g, index;
L_g=left;
R_g=right;
fix=mas[left];
while(left<right)
{
    while((mas[right]>fix)&&(left<right)) right--;
    if(left!=right){ mas[left]=mas[right]; left++; }
    while((mas[left]<fix)&&(left<right)) left++;
    if(left!=right){ mas[right]=mas[left]; right--; }
}
mas[left]=fix;
index=left;
right=R_g;
left=L_g;
if(left<index) Qsort(mas, left, index-1);
if(right>index) Qsort(mas, index+1, right);
}
