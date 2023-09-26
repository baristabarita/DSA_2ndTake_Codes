Data Struct Def:

#define CSIZE   0X3E8    //Close hash table size
#define OSIZE   0XF      //Open hash table size
#define EMPTY   "000000" //Assign to ID field
#define DELETED "xxxxxx" //Assign to ID field

typedef struct{
    char name[24];     //Chocolate name
    int weight;        //Chocolate weight in grams
}chocoDesc;

typedef struct{
    char prodID[8];      //product ID uniquely identifies the products; 
                           EMPTY or DELETED
    chocoDesc prodDesc;  //product description
    float prodPrice;     //product price
    int prodQty;       
}product;                //product record

typedef struct node{
    product prod;
    struct node *pLink;
}*prodPtr;

typedef struct{
    prodPtr Header[OSIZE];
    int count;             //holds the number of elements
}OpenHash; 		   //Open Hashing

typedef struct{
    product Header[OSIZE];
    int elemCtr;             //holds the number of elements
}CloseHash; 		     //Closed Hashing

CloseHash removeChoco(OpenHash *O){
    int index, j, hashValue;
    prodPtr* pptr;
    CloseHash* C;
    for(index=0;index<OSIZE;index++){
        for(pptr=&(O->Header[index]);*pptr!=NULL;pptr=&(O->Header[index].pLink)){
            if(O->Header[index].prod.prodDesc.weight<=100){
                hashValue = hash(O->Header[index].prod.prodID);
                if(strcmp(C.Htable[hashValue].prod.prodID,EMPTY)==0||strcmp(C.Htable[hashValue].prod.prodID,DELETED)==0){
                     C.Htable[hashValue].prod=O->Header[index].prod;
                }else{
                    for(j=hashValue+1;
                       j!=hashValue&&strcmp(C.Htable[hashValue].prod.prodID,EMPTY)!=0||strcmp(C.Htable[hashValue].prod.prodID,DELETED)!=0;j++){}
                    if(j!=hashValue){
                         C.Htable[j].prod=O->Header[index].prod;
                    }   
                }
            
            }
        }
    }
    return C;   
}
