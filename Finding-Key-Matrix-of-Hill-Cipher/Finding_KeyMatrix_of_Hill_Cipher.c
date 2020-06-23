#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int mod26(int a){   // to find mod 26
    a=a%26;
    if(a<0){
        a=a+26;
    }
    return a;
}

int mod13(int a){   // to find mod 13
    a=a%13;
    if(a<0){
        a=a+13;
    }
    return a;
}

int inversemod26(int a){    // to find inverse mod 26
    for(int i=1;i<26;i++){
        if((a*i)%26 ==1) return i;
    }
    return 0;
}

int inversemod13(int a){    // to find inverse mod 13
    for(int i=1;i<13;i++){
        if((a*i)%13 ==1) return i;
    }
    return 0;
}

bool isInvertible(int a,int b,int c,int d){ // to check whether key matrix is invertable
    int val=mod26(a*d - b*c);
    if(inversemod26(val)==0)return false;
    else return true;
}

bool isCorrectKey(int a,int b,int c,int d,int p[][2],int q[][2]){ // to check whether found key matrix is solution
    int a1,b1,c1,d1;
    a1=mod26(a*p[0][0] + b*p[1][0]);
    b1=mod26(c*p[0][0] + d*p[1][0]);
    c1=mod26(a*p[0][1] + b*p[1][1]);
    d1=mod26(c*p[0][1] + d*p[1][1]);
    if(a1==q[0][0] && b1==q[1][0] && c1==q[0][1] && d1==q[1][1]) return true;
    else return false;
}

void findKey(int p[][2],int c[][2]){    // to find solution key matrix [a,b]
                                        //                             [c,d]
    
    int a1=p[0][0],b1=p[1][0],v1=c[0][0];   //1           // linear equations of the form ax+by=c
    int a2=p[0][1],b2=p[1][1],v2=c[0][1];   //2
    int c1=p[0][0],d1=p[1][0],v3=c[1][0];   //3
    int c2=p[0][1],d2=p[1][1],v4=c[1][1];   //4
    
    int a_val[2],b_val[2],c_val[2],d_val[2], l,r;
    
    l=mod26(mod26(a1*b2) - mod26(a2*b1));   // Solving equations 1,2 to find a
    r=mod26(mod26(v1*b2) - mod26(v2*b1));
    if(inversemod26(l)==0){                 // if (l mod 26) doesn't have any inverse
        l=l/2; r=r/2;
        r=mod13(r * inversemod13(l));
        a_val[0]=r;                         // as we found in mod 13 there exists two values for mod 26
        a_val[1]=r+13;
    }
    else{
        r=mod26(r*inversemod26(l));
        a_val[0]=r;
        a_val[1]=0;
    }
    
    l=mod26(mod26(b1*a2) - mod26(b2*a1));   // Solving equations 1,2 to find b
    r=mod26(mod26(v1*a2) - mod26(v2*a1));
    if(inversemod26(l)==0){
        l=l/2; r=r/2;
        r=mod13(r * inversemod13(l));
        b_val[0]=r;
        b_val[1]=r+13;
    }
    else{
        r=mod26(r*inversemod26(l));
        b_val[0]=r;
        b_val[1]=0;
    }
    
    l=mod26(mod26(c1*d2) - mod26(c2*d1));   // Solving equations 3,4 to find c
    r=mod26(mod26(v3*d2) - mod26(v4*d1));
    if(inversemod26(l)==0){
        l=l/2; r=r/2;
        r=mod13(r * inversemod13(l));
        c_val[0]=r;
        c_val[1]=r+13;
    }
    else{
        r=mod26(r*inversemod26(l));
        c_val[0]=r;
        c_val[1]=0;
    }
    
    l=mod26(mod26(d1*c2) - mod26(d2*c1));   // Solving equations 3,4 to find d
    r=mod26(mod26(v3*c2) - mod26(v4*c1));
    if(inversemod26(l)==0){
        l=l/2; r=r/2;
        r=mod13(r * inversemod13(l));
        d_val[0]=r;
        d_val[1]=r+13;
    }
    else{
        r=mod26(r*inversemod26(l));
        d_val[0]=r;
        d_val[1]=0;
    }
    
    int flag=0;                         // to check all 16 possible key matrices
    for(int i=0;i<2 && flag==0;i++){
        for(int j=0;j<2 && flag==0;j++){
            for(int k=0;k<2 && flag==0;k++){
                for(int x=0;x<2 && flag==0;x++){
                    
                    if(a_val[i]!=0 && b_val[j]!=0 && c_val[k]!=0 && d_val[x]!=0 ){  // to check if any value 0
                        
                        if( isInvertible( a_val[i], b_val[j], c_val[k], d_val[x] ) ){   // to check whether it is invertable
                            
                            if( isCorrectKey( a_val[i], b_val[j], c_val[k], d_val[x], p,c ) ){  // to check mulitiplying it with plain matrix are whether we are getting cypher matrix or not
                                
                                printf("%d %d %d %d",a_val[i], b_val[j], c_val[k], d_val[x]);
                                flag=1;
                            }
                        }
                    }
                    
                }
            }
        }
    }
    
}

int main(){
    
    char p_text[10],c_text[10];
    gets(p_text);
    gets(c_text);
    
    int p[2][2],c[2][2];
    int k;
    
    k=0;
    for(int i=0;i<2;i++){           // storing values in matrices in [a-z]=[1-26] formate
        for(int j=0;j<2;j++){
            p[j][i]=(p_text[k] % 97)+1 ;
            c[j][i]=(c_text[k] % 65)+1 ;
            k++;
        }
    }
    
   findKey(p,c);
    
    return 0;
}

