#include<stdio.h>
#include<stdlib.h>

#define FATHER(child) (struct Father *)(child)

void print1(int i)
{
    printf("this is father and i = %d\n",i);
}

void print2(int i)
{
    printf("this is child  and i = %d\n",i);
}

// 父类
struct Father {
    int  a;
    void (*pointer1_to_function)(int);
};

// 子类
struct Child {
    struct Father f;
    int b;
    void (*pointer2_to_function)(int);
};

void father_member_funtion(struct Father *f,char *string)
{
    printf("\n");
    f->pointer1_to_function(f->a);
    printf("%s\n\n",string);
}

int main()
{
    struct Child *p_child;
    p_child = (struct Child *)malloc(sizeof(struct Child));
    p_child->f.a = 10;
    p_child->f.pointer1_to_function = print1;
    p_child->b   = 20;
    p_child->pointer2_to_function   = print2;

    p_child->pointer2_to_function(p_child->b);

    struct Father *p_father = FATHER(p_child);
    p_father->pointer1_to_function(p_father->a);

    father_member_funtion(p_child,"hello");

    return 0;
}
