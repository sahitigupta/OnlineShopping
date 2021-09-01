#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//structure of a product
struct object
{
    char name[20];
    int price, quantity, key;	// key: refers to product id
    struct object *link;
};

// i represents the index for users - which is used as user id
static int i = 0;		
typedef struct object *obj;
obj h, t, t1;

//structure of user
struct user
{
    char name[20], pw[20];
    long long ph;
    int ukey;		// user id
    struct user *link;
    obj head;		// for cart
}*us = NULL, *f = NULL, *temp = NULL, *temp1 = NULL;


//A new user can add his account by signing up//
void signup()             
{
    char name[20], pw[20];
    obj hd;	// user cart
    long long phno;
    us = (struct user *)malloc(sizeof(struct user));
    hd = (obj)malloc(sizeof(struct object));
    hd->link=NULL;
    
    printf("Enter your details : \n");
    printf("Name : ");
    scanf("%s", name);
    printf("Ph.No: ");
    scanf("%lld", &phno);
    printf("Password : ");
    scanf("%s", pw);
    
    strcpy(us->name, name);
    strcpy(us->pw, pw);
    us->ph = phno;
    us->ukey = i;
    us->link=NULL;
    us->head=hd;
    i++;
    
    if (f == NULL)
    {	// first user
        f = us;
    }
    else
    {	// if users list is not empty
        temp = f;
        while (temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = us;
    }
}

// The 'display(obj p)' function displays the name, quantity, price of item('p') chosen from the cart//
void display(obj p)              
{
    obj q = p;
    
    
    if (q == NULL)
    {	// if the cart is empty
        printf("\nEmpty cart\n");
    }
    else
    {	// display the details
    	printf("\nYour cart\n");
        printf("Key\tName\t\tQty\tPrice(for each)\n");
        while (q != NULL)
        {
            printf("%d\t%s\t\t%d\t%d\n", q->key,q->name, q->quantity, q->price);
            q = q->link;
        }
    }
}

// The list() function displays the list of items available in the shop//
int list()                       
{
    int ch;
    printf("Enter choice\n");
    printf("1.Pens\n");
    scanf("%d",&ch);
    printf("Available objects\n");
    display(h);
    return ch;
}

// The add(int key , int ch) returns the pointer to the product searched by the user//
obj add(int key, int ch)              
{
    obj temp=h;
    
    if(temp==NULL)
    {	// If the shop has no products
        printf("\n....Products are coming soon....\n");
        return h;
    }
    else
    {	// If the shop has some stock of product with id = key, return the pointer to the product
        while(temp!=NULL)
        {
            if(temp->key==key)
                return temp;
            temp=temp->link;
        }
        return NULL;
    }
}

// User account //
void account(obj k)
{
    int uc,ch;
    int key;
    obj temp,temp1=NULL,temp2=NULL,temp3=NULL;
    printf("\nWelcome\n");
    while(1)
    {
        printf("\n-----User account-----\n");
        printf("1.Add item\n2.Delete an item\n3.Place order\n4.Cart\n5.Logout\n");
        scanf("%d", &uc);
        switch (uc)
        {
        
        case 1:                   //-----Adding item to the user's cart-------//
            ch=list();
            printf("Enter the key\n");
            scanf("%d",&key);
            temp=add(key,ch);
            if(temp)
            {
                if(temp->quantity!=0)
                {	
                    // If the stock of the chosen product is present
                    
                    temp2 = (obj)malloc(sizeof(struct object));
                    temp2->key=temp->key;
                    temp2->price=temp->price;
                    temp2->quantity=1;
                    strcpy(temp2->name,temp->name);

                    if (k->link == NULL)
                    {	// If the user's cart is empty, add the product to the cart
                        k->link = temp2;
                        temp2->link=NULL;
                    }
                    else
                    {	// The user's cart is not empty. 
                    	// Checking if the product is already present in the cart
                        temp1=k->link;
                        while(temp1!=NULL)
                        {
                            if(temp1->key==temp2->key)
                            {
                                break;
                            }
                            temp3=temp1;
                            temp1=temp1->link;
                        }
                        // Not reached end of the list
                        if(temp1!=NULL)
                        {   
                            if(temp1->key!=temp2->key)
                            {	// If the product is not found in the cart, add the product
                                temp2->link=k->link;
                                k->link=temp2;
                            }
                            else		//If the product is found in the cart, increment the quantity
                                temp1->quantity++;
                        }
                        else
                        {   // If end of the list is reached
                            temp2->link=k->link;
                            k->link=temp2;
                        }
                    }
                    // Since the product is added to the cart, decrement the quantity of stock in the shop
                    temp->quantity--;
                    printf("Added successfully\n");
                }
                else	// Since quantity is 0
                    printf("Out of stock\n");
            }
            else	// Shop has no products
                printf("Out of stock\n");
            break;
            
            
        case 2:                                  //-----Deleting an item from user's cart------//
            if (k->link == NULL)
            {
                printf("Empty cart\n");
                break;
            }
            else
            {	// Display the cart of user identified by the pointer k
                display(k->link);
                printf("Enter key of the product to be deleted\n");
                scanf("%d",&key);
                temp=k->link;

                while(temp!=NULL)
                {
		   // Finding tht product with id=key in the cart
                    temp2=temp;
                    if(temp2->key==key)
                    {
                        break;
                    }
                    temp2=temp2->link;
                }
                if(temp2!=NULL)
                {   // If the product found on the cart
                
                 
                        if(temp2->quantity==0)
                        {
                            //temp->link=temp2->link;
                            //temp2=NULL;
                        }
                        else{
                            temp->quantity--;	// decrement the item in cart
                            temp2=add(key, ch);
                            
                            if(temp2){
                                temp2->quantity++;	// increment the stock
                            }
                            
                        }
                    
		       printf("Product quantity decremented successfully\n");
                }
                else
                    printf("Product key not found\n");
            }
            break;
            
        case 3:                                    //Placing order//
             printf("Enter key to place order\n");
            scanf("%d",&key);
            printf("Order placed\n");
            break;
            
        case 4:                                    //Checking the items in user's cart//
            display(k->link);
            int cost=0;
            temp1=k->link;
            while(temp1!=NULL)
            {
                cost+=(temp1->quantity)*(temp1->price);
                temp1=temp1->link;
            }
            printf("Cart total : %d\n",cost);
            break;
        }
        if(uc==5)
            break;
    }
}

// Admin can add items by setting name , quantity , price of the items.//
void setprice()                        
{
    char b[50];
    int price;
    printf("\nContent updates by admin\n");
    printf("Enter the object name\n");
    scanf("%s",b);
    t = (obj)malloc(sizeof(struct object));
    strcpy(t->name, b);
    printf("Enter the price\n");
    scanf("%d", &price);
    t->price=price;
    printf("Enter quantity\n");
    scanf("%d", &t->quantity);
    printf("Enter key\n");
    scanf("%d",&t->key);
    t->link=NULL;
    if (h== NULL)
    {
        h= t;
    }
    else
    {
        t1=h;
        while(t1->link!=NULL)
            t1=t1->link;
        t1->link=t;
    }
}

// Existing user can directly login to his account.//
void login(int ad)              
{
    long ph;
    char name[20], pw[20], ln[20], lpw[20];
    int flag1 = 0, op, c1, c2, lk, lph;
    obj head1,fg=NULL;
    printf("\n----Enter the details----\n");
    printf("User name : ");
    scanf("%s", name);
    printf("Password : ");
    scanf("%s", pw);
    int k=0;
    for (temp1 = f; temp1!=NULL; temp1 = temp1->link)
    {
        strcpy(ln, temp1->name);
        strcpy(lpw, temp1->pw);
        head1=temp1->head;
        c1 = strcmp(ln, name);
        c2 = strcmp(lpw, pw);
        if (c1 == 0 && c2 == 0)
        {
            fg = head1;
            flag1 = 1;
            break;
        }
        k++;
    }
    if (flag1 == 1)
    {
        printf("Login Successful\n");
        if (ad == 0)
            account(fg);
        else if (ad == 1)
        {
            int s;
            while(1)
            {
                printf("\n----Update the items----\n");
                printf("1.Pens\n2.Logout\n");
                scanf("%d", &s);
                if(s==2)
                    break;
                setprice();
            }
        }
        return;
    }
    printf("Invalid username or password\n");
}

void main()
{
    int ch;
       
    while (1)
    {
        printf("\n------On-line shopping portal--------\n");
   	printf("1.New user then press 1\n");
    	printf("2.Existing user the press 2 for login\n3.Admin\n");
    	printf("4.Exit\n");
        printf("Enter choice\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            signup();
            break;
        case 2:
            login(0);
            break;
        case 4:
            exit(0);
        case 3:
            login(1);
            break;
        }
    }
}
