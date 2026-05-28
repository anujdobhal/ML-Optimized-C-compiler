%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.c"

#include <ctype.h>

// ---------------- AST NODE ----------------

typedef struct ASTNode
{
    char type[20];
    char value[50];

    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *middle;
    struct ASTNode *next;

} ASTNode;

ASTNode* createNode(char *type,
                    char *value,
                    ASTNode *left,
                    ASTNode *right,
                    ASTNode *middle)
{
    ASTNode *node =
        (ASTNode*)malloc(sizeof(ASTNode));

    strcpy(node->type,type);

    if(value)
        strcpy(node->value,value);
    else
        strcpy(node->value,"");

    node->left = left;
    node->right = right;
    node->middle = middle;
    node->next = NULL;

    return node;
}

extern int yylineno;
extern FILE *yyin;
extern char *yytext;


int yylex();
int yyerror(char *s);
int printline();

// ----------- ICG (YOUR PART) -----------
int tempCount = 0;

char* newTemp() {
    char *temp = (char*)malloc(10);
    sprintf(temp, "t%d", tempCount++);
    return temp;
}
int labelCount = 0;

char* newLabel()
{
    char *label = (char*)malloc(10);

    sprintf(label, "L%d", labelCount++);

    return label;
}

char tac[1000][100];


int tacIndex = 0;

void emit(char *str) {
    strcpy(tac[tacIndex++], str);
}

// ----------- existing variables -----------
int i=1,k=-1,l=-1;
int j=0;
char curfunc[100];
int stack[100];
int top=0;
int plist[100],flist[100];
int end[100];
int arr[10];
int ct=0,c=0,b;
int loop = 0;
int errc=0;
int type=0;
ASTNode *root = NULL;
%}

%token<ival> INT FLOAT VOID
%token<str> ID NUM REAL STRING
%token WHILE IF RETURN PREPROC LE PRINT FUNCTION DO ARRAY ELSE STRUCT STRUCT_VAR FOR GE EQ NE INC DEC
%right '='
%left '+' '-'
%left '*' '/'
%left '<' '>' LE GE EQ NE
%nonassoc IFX
%nonassoc ELSE

%type<node> stmt if while for dowhile expr1 exp assignment1 assignment2 Declaration CompoundStmt stmtlist Function
%type<str> consttype
%type<ival> Type

%union
{
	int ival;
	char *str;
	struct ASTNode *node;
}

%%

start :
start stmt
{
    if($2 != NULL)
    {
        if(root == NULL)
        {
            root = $2;
        }
        else
        {
            ASTNode *temp = root;

            while(temp->next != NULL)
                temp = temp->next;

            temp->next = $2;
        }
    }
}

| start Function
{
    if($2 != NULL)
    {
        if(root == NULL)
        {
            root = $2;
        }
        else
        {
            ASTNode *temp = root;

            while(temp->next != NULL)
                temp = temp->next;

            temp->next = $2;
        }
    }
}

| start Declaration
{
    if($2 != NULL)
    {
        if(root == NULL)
        {
            root = $2;
        }
        else
        {
            ASTNode *temp = root;

            while(temp->next != NULL)
                temp = temp->next;

            temp->next = $2;
        }
    }
}

| start PREPROC

|
;

Function :
Type ID '(' ')' CompoundStmt
{

    ASTNode *funcNode =
        createNode("FUNCTION",$2,$5,NULL,NULL);

    $$ = funcNode;

}
;

parameter_list : parameter_list ',' parameter
               | parameter
               ;

parameter : Type ID {plist[++k]=$1;insert($2,$1);insertscope($2,i);}
          ;

Type : INT
	| FLOAT
	| VOID
	;

stmt :
Declaration
{
    $$ = $1;
}

| if
{
    $$ = $1;
}

| for
{
    $$ = $1;
}

| while
{
    $$ = $1;
}

| dowhile
{
    $$ = $1;
}

| assignment1 ';'
{
    $$ = $1;
}

| RETURN consttype ';'
{
    $$ = createNode("RETURN",$2,NULL,NULL,NULL);
}

| RETURN ID ';'
{
    $$ = createNode("RETURN",$2,NULL,NULL,NULL);
}

| PRINT '(' STRING ')' ';'
{
    $$ = createNode("PRINT",$3,NULL,NULL,NULL);
}

| CompoundStmt
{
    $$ = $1;
}

| ';'
{
    $$ = NULL;
}
;

CompoundStmt :
'{' stmtlist '}'
{
    $$ = $2;
}
;


stmtlist :
stmtlist stmt
{
    if($1 == NULL)
    {
        $$ = $2;
    }
    else
    {
        ASTNode *temp = $1;

        while(temp->next != NULL)
            temp = temp->next;

        temp->next = $2;

        $$ = $1;
    }
}

| stmt
{
    $$ = $1;
}

|
{
    $$ = NULL;
}
;
dowhile :
DO CompoundStmt WHILE '(' expr1 ')' ';'
{
    $$ = createNode("DOWHILE","dowhile",$5,$2,NULL);
}
;

if :
IF '(' expr1 ')' CompoundStmt %prec IFX
{
    $$ = createNode("IF","if",$3,$5,NULL);
}

| IF '(' expr1 ')' CompoundStmt ELSE CompoundStmt
{
    $$ = createNode("IFELSE","ifelse",$3,$5,$7);
}
;

for :
FOR '(' assignment1 ';' expr1 ';' assignment1 ')'
CompoundStmt
{
    ASTNode *forNode =
        createNode("FOR","for",$3,$5,$7);

    forNode->next = $9;

    $$ = forNode;
}
;

while :
WHILE '(' expr1 ')' CompoundStmt
{
    $$ = createNode("WHILE","while",$3,$5,NULL);

    
}
;

expr1 : expr1 LE expr1
{
    $$ = createNode("LE","<=",$1,$3,NULL);
}

| expr1 GE expr1
{
    $$ = createNode("GE",">=",$1,$3,NULL);
}

| expr1 NE expr1
{
    $$ = createNode("NE","!=",$1,$3,NULL);
}

| expr1 EQ expr1
{
    $$ = createNode("EQ","==",$1,$3,NULL);
}

| expr1 '>' expr1
{
    $$ = createNode("GT",">",$1,$3,NULL);
}

| expr1 '<' expr1
{
    $$ = createNode("LT","<",$1,$3,NULL);
}

| assignment1
{
    $$ = $1;
}
;
assignment : ID '=' consttype
	| ID '+' assignment
	| ID ',' assignment
	| consttype ',' assignment
	| ID
	| consttype
	;

assignment1 : ID '=' assignment1
{
    ASTNode *idNode =
        createNode("ID",$1,NULL,NULL,NULL);

    $$ = createNode("ASSIGN","=",idNode,$3,NULL);

    int sct = returnscope($1, stack[top-1]);
    int type = returntype($1, sct);

    if(type == 273)
    {
        printf("\nError : Type Mismatch : Line %d\n", printline());
        errc++;
    }
}

	| ID ',' assignment1
	{
		if(lookup($1)) {
			printf("\nUndeclared Variable %s : Line %d\n",$1,printline()); errc++;
        }
        $$ = createNode("COMMA", ",", createNode("ID", $1, NULL, NULL, NULL), $3, NULL);
	}
    | assignment2
    {
     $$ = $1;
    }
	| consttype ',' assignment1
    {
        $$ = createNode("COMMA", ",", createNode("NUM", $1, NULL, NULL, NULL), $3, NULL);
    }
	| ID
{
   if(lookup($1))
   {
      printf("\nUndeclared Variable %s : Line %d\n",
             $1,
             printline());

      errc++;
   }

   $$ = createNode("ID",$1,NULL,NULL,NULL);
}
	| ID '=' ID '(' paralist ')'			//function call
        {
                int sct=returnscope($1,stack[top-1]);
		int type=returntype($1,sct);
                //printf("%s",$3);
                int rtype;
                rtype=returntypef($3); int ch=0;
                //printf("%d",rtype);
		if(rtype!=type)
			{ printf("\nError : Type Mismatch : Line %d\n",printline()); errc++;}
		if(!lookup($1))
		{
		  for(j=0;j<=l;j++)
                  {ch = ch+checkp($3,flist[j],j);}
                  if(ch>0) { printf("\nError : Parameter Type Mistake or Function undeclared : Line %d\n",printline()); errc++;}
                  l=-1;
		}
        ASTNode *idNode = createNode("ID", $1, NULL, NULL, NULL);
        ASTNode *callNode = createNode("CALL", $3, NULL, NULL, NULL);
        $$ = createNode("ASSIGN", "=", idNode, callNode, NULL);
	}
	| ID '(' paralist ')'			//function call without assignment
	{
                int sct=returnscope($1,stack[top-1]);
		int type=returntype($1,sct); int ch=0;
		if(!lookup($1))
		{
		  for(j=0;j<=l;j++)
                  {ch = ch+checkp($1,flist[j],j);}
                  if(ch>0) { printf("\nError : Parameter Type Mistake or Required Function undeclared : Line %d\n",printline()); errc++;}
                  l=-1;
		}
                else {printf("\nUndeclared Function %s : Line %d\n",$1,printline());errc++;}
        $$ = createNode("CALL", $1, NULL, NULL, NULL);
	}
/*	| ID '[' ID ']' '=' ID
	{
        	int sct=returnscope($1,stack[top-1]); 
		int itype=returntype($3,sct);
                int type=returntype2($1,sct); int ch=0;
                int rtype=returntype($6,sct);
                if(itype!=258)
                        { printf("\nError : Array index must be of type int : Line %d\n",printline());errc++;}
		if(rtype!=type)
			{ printf("\nError : Type Mismatch : Line %d\n",printline()); errc++;}
	}*/
	| consttype
    {
        $$ = createNode("NUM", $1, NULL, NULL, NULL);
    }
	;

paralist : paralist ',' param
         | param
         ;

param : ID
	{
                if(lookup($1))
	        	{printf("\nUndeclared Variable %s : Line %d\n",$1,printline());errc++;}
                else
                {
                	int sct=returnscope($1,stack[top-1]);
                	flist[++l]=returntype($1,sct);
                }
	}
	;

assignment2 : ID '=' exp
{
    ASTNode *idNode =
        createNode("ID",$1,NULL,NULL,NULL);

    $$ = createNode("ASSIGN","=",idNode,$3,NULL);

    c=0;
}

| ID '=' '(' exp ')'
{
    ASTNode *idNode =
        createNode("ID",$1,NULL,NULL,NULL);

    $$ = createNode("ASSIGN","=",idNode,$4,NULL);

    c=0;
}
;

exp : ID
{
    if(c==0)
    {
        c=1;
        int sct=returnscope($1,stack[top-1]);
        b=returntype($1,sct);
    }
    else
	{
    int sct1=returnscope($1,stack[top-1]);
    // temporarily skip strict type checking
	}

    $$ = createNode("ID",$1,NULL,NULL,NULL);
}

| exp '+' exp
{
    $$ = createNode("ADD","+",$1,$3,NULL);
}

| exp '-' exp
{
    $$ = createNode("SUB","-",$1,$3,NULL);
}

| exp '*' exp
{
    $$ = createNode("MUL","*",$1,$3,NULL);
}

| exp '/' exp
{
    $$ = createNode("DIV","/",$1,$3,NULL);
}

| '(' exp ')'
{
    $$ = $2;
}

| consttype
{
    $$ = createNode("NUM",$1,NULL,NULL,NULL);
}
;

consttype : NUM
	| REAL
	;

Declaration : Type ID '=' consttype ';'
	{
		if( (!(strspn($4,"0123456789")==strlen($4))) && $1==258)
			{printf("\nError : Type Mismatch : Line %d\n",printline());errc++;}
                else if ($1==273)  {printf("\nError : Type Mismatch : Line %d\n",printline());errc++;}
		if(!lookup($2))
		{
			int currscope=stack[top-1];
			int previous_scope=returnscope($2,currscope);
			if(currscope==previous_scope)
				{printf("\nError : Redeclaration of %s : Line %d\n",$2,printline());errc++;}
			else
			{
				insert_dup($2,$1,currscope);
				check_scope_update($2,$4,stack[top-1]);
			}
		}
		else
		{
			int scope=stack[top-1];
			insert($2,$1);
			insertscope($2,scope);
			check_scope_update($2,$4,stack[top-1]);
		}
            ASTNode *idNode =
            createNode("ID",$2,NULL,NULL,NULL);

        ASTNode *valueNode =
            createNode("NUM",$4,NULL,NULL,NULL);

        $$ = createNode("DECL","=",idNode,valueNode,NULL);
	}

        | Type ID ';'
        {
        	if(!lookup($2))
		{
			int currscope=stack[top-1];
			int previous_scope=returnscope($2,currscope);
			if(currscope==previous_scope)
				{printf("\nError : Redeclaration of %s : Line %d\n",$2,printline());errc++;}
			else
			{
				insert_dup($2,$1,currscope);
				//check_scope_update($2,$4,stack[top-1]);
			}
		}
		else
		{
			int scope=stack[top-1];
			//printf("%d",type);
			insert($2,$1);
			insertscope($2,scope);
			//check_scope_update($2,$4,stack[top-1]);
		}
        ASTNode *idNode =
        createNode("ID",$2,NULL,NULL,NULL);

        $$ = createNode("DECL",$2,idNode,NULL,NULL);
	}
	| Type ID '[' consttype ']' ';' {
                       int itype;
                       if(!(strspn($4,"0123456789")==strlen($4))) { itype=259; } else itype = 258;
                       if(itype!=258)
                       { printf("\nError : Array index must be of type int : Line %d\n",printline());errc++;}
                       if(atoi($4)<=0)
                       { printf("\nError : Array index must be of type int > 0 : Line %d\n",printline());errc++;}
                       if(!lookup($2))
		       {
			int currscope=stack[top-1];
			int previous_scope=returnscope($2,currscope);
			if(currscope==previous_scope)
				{printf("\nError : Redeclaration of %s : Line %d\n",$2,printline());errc++;}
			else
			{

				insert_dup($2,ARRAY,currscope);
                                insert_by_scope($2,$1,currscope);	//to insert type to the correct identifier in case of multiple entries of the identifier by using scope
                                if (itype==258) {insert_index($2, atoi($4));}
			}
		      }
		      else
		      {
			int scope=stack[top-1];
                        insert($2,ARRAY);
			insert($2,$1);
			insertscope($2,scope);
                        if (itype==258) {insert_index($2, atoi($4));}
		      }
        ASTNode *idNode = createNode("ID", $2, NULL, NULL, NULL);
        ASTNode *sizeNode = createNode("NUM", $4, NULL, NULL, NULL);
        $$ = createNode("DECL_ARRAY", $2, idNode, sizeNode, NULL);
		    }
	| STRUCT ID '{' stmtlist '}' ';' {
						insert($2,STRUCT);
                        $$ = createNode("STRUCT_DECL", $2, $4, NULL, NULL);
						}
	| STRUCT ID ID ';' {
				insert($3,STRUCT_VAR);
                $$ = createNode("STRUCT_VAR_DECL", $3, createNode("ID", $2, NULL, NULL, NULL), NULL, NULL);
				}
	| error
	;



%%

#include<ctype.h>

void printAST(ASTNode *node, int level)
{
    ASTNode *curr = node;
    while(curr != NULL)
    {
        for(int i = 0; i < level; i++)
            printf("  ");

        printf("%s", curr->type);
        if(curr->value && strlen(curr->value) > 0)
            printf(" (%s)", curr->value);
        printf("\n");

        if(curr->left)
            printAST(curr->left, level + 1);
        if(curr->middle)
            printAST(curr->middle, level + 1);
        if(curr->right)
            printAST(curr->right, level + 1);

        curr = curr->next;
    }
}

char* generateTAC(ASTNode *node)
{
    if(node == NULL)
        return "";
	ASTNode *curr = node;

while(curr != NULL)
{
    // ---------- FUNCTION ----------
    if(strcmp(curr->type,"FUNCTION")==0)
    {
        emit("");

        char label[100];

        sprintf(label,"\nFUNC %s:",curr->value);

        emit(label);

        generateTAC(curr->left);

        curr = curr->next;
        continue;
    }

    // ---------- NUMBER ----------
    if(strcmp(curr->type,"NUM")==0)
    {
        return curr->value;
    }

    // ---------- ID ----------
    if(strcmp(curr->type,"ID")==0)
    {
        return  curr->value;;
    }

    // ---------- ADD ----------
    if(strcmp(curr->type,"ADD")==0)
    {
        char *left = generateTAC(curr->left);

        char *right = generateTAC(curr->right);

        char *temp = newTemp();

        char code[100];

        sprintf(code,"%s = %s + %s",
                temp,left,right);

        emit(code);

        return temp;
    }

    // ---------- SUB ----------
    if(strcmp(curr->type,"SUB")==0)
    {
        char *left = generateTAC(curr->left);

        char *right = generateTAC(curr->right);

        char *temp = newTemp();

        char code[100];

        sprintf(code,"%s = %s - %s",
                temp,left,right);

        emit(code);

        return temp;
    }

    // ---------- MUL ----------
    if(strcmp(curr->type,"MUL")==0)
    {
        char *left = generateTAC(curr->left);

        char *right = generateTAC(curr->right);

        char *temp = newTemp();

        char code[100];

        sprintf(code,"%s = %s * %s",
                temp,left,right);

        emit(code);

        return temp;
    }

    // ---------- DIV ----------
    if(strcmp(curr->type,"DIV")==0)
    {
        char *left = generateTAC(curr->left);

        char *right = generateTAC(curr->right);

        char *temp = newTemp();

        char code[100];

        sprintf(code,"%s = %s / %s",
                temp,left,right);

        emit(code);

        return temp;
    }
	// ---------- RELATIONAL ----------
	if(
    	strcmp(curr->type,"LT")==0 ||
    	strcmp(curr->type,"GT")==0 ||
    	strcmp(curr->type,"LE")==0 ||
    	strcmp(curr->type,"GE")==0 ||
    	strcmp(curr->type,"EQ")==0 ||
    	strcmp(curr->type,"NE")==0
	)
	{
    char *left = generateTAC(curr->left);

    char *right = generateTAC(curr->right);

    char *temp = newTemp();

    char code[100];

    sprintf(code,
        "%s = %s %s %s",
        temp,
        left,
       	curr->value ,
        right);

    emit(code);

    return temp;
	}
    // ---------- ASSIGN ----------
    if(strcmp(curr->type,"ASSIGN")==0)
    {
        char *rhs = generateTAC(curr->right);

        char code[100];

        sprintf(code,"%s = %s",
                curr->left->value,
                rhs);

        emit(code);

        curr = curr->next;
        continue;
    }
    // ---------- CALL ----------
    if(strcmp(curr->type,"CALL")==0)
    {
        char *temp = newTemp();
        char code[100];
        sprintf(code,"%s = call %s", temp, curr->value);
        emit(code);
        return temp;
    }
    // ---------- COMMA ----------
    if(strcmp(curr->type,"COMMA")==0)
    {
        generateTAC(curr->left);
        return generateTAC(curr->right);
    }
    // ---------- DECL ----------
    if(strcmp(curr->type,"DECL")==0)
    {
        if(curr->right != NULL)
        {
            char code[100];

            sprintf(code,
                "%s = %s",
                curr->left->value,
                curr->right->value);

            emit(code);
        }

        curr = curr->next;
        continue;
    }
    // ---------- WHILE ----------
    if(strcmp(curr->type,"WHILE")==0)
    {
        char *start = newLabel();

        char *end = newLabel();

        char code[100];

        sprintf(code,"%s:",start);
        emit(code);

        char *cond =
            generateTAC(curr->left);

        sprintf(code,
            "ifFalse %s goto %s",
            cond,end);

        emit(code);

        generateTAC(curr->right);

        sprintf(code,"goto %s",start);
        emit(code);

        sprintf(code,"%s:",end);
        emit(code);
        curr = curr->next;
        continue;
    }
        // ---------- IF ----------
    if(strcmp(curr->type,"IF")==0)
    {
        char *end = newLabel();

        char code[100];

        char *cond =
            generateTAC(curr->left);

        sprintf(code,
                "ifFalse %s goto %s",
                cond,end);

        emit(code);

        generateTAC(curr->right);

        sprintf(code,"%s:",end);

        emit(code);
        curr = curr->next;
        continue;    }
        // ---------- IF ELSE ----------
    if(strcmp(curr->type,"IFELSE")==0)
    {
        char *elseLabel = newLabel();

        char *endLabel = newLabel();

        char code[100];

        char *cond =
            generateTAC(curr->left);

        sprintf(code,
                "ifFalse %s goto %s",
                cond,elseLabel);

        emit(code);

        generateTAC(curr->right);

        sprintf(code,
                "goto %s",
                endLabel);

        emit(code);

        sprintf(code,"%s:",elseLabel);

        emit(code);

        generateTAC(curr->middle);

        sprintf(code,"%s:",endLabel);

        emit(code);
        curr = curr->next;
        continue;
    }
    // ---------- FOR ----------
    if(strcmp(curr->type,"FOR")==0)
    {
        char *start = newLabel();

        char *end = newLabel();

        char code[100];

        // INIT
        generateTAC(curr->left);

        sprintf(code,"%s:",start);
        emit(code);

        // CONDITION
        char *cond =
         generateTAC(curr->right);

        sprintf(code,
            "ifFalse %s goto %s",
            cond,end);

        emit(code);

        // BODY
        generateTAC(curr->next);

        // UPDATE
        generateTAC(curr->middle);

        sprintf(code,"goto %s",start);

        emit(code);

        sprintf(code,"%s:",end);

        emit(code);
        curr = curr->next;
        continue;
    }
        // ---------- RETURN ----------
    if(strcmp(curr->type,"RETURN")==0)
    {
        char code[100];

        sprintf(code,
                "return %s",
                curr->value);

        emit(code);
        curr = curr->next;
        continue;
    }
        // ---------- PRINT ----------
    if(strcmp(curr->type,"PRINT")==0)
    {
        char code[100];

        sprintf(code,
                "print %s",
                curr->value);

        emit(code);
        curr = curr->next;
        continue;
    }
    curr = curr->next;
    }

    return "";
}
int main(int argc, char *argv[])

{
    yyin = fopen(argv[1], "r");

    if(!yyparse() && errc<=0)
    {
        printf("\nParsing Completed\n");
        display();
        
        printf("\nAbstract Syntax Tree (AST):\n");
        printAST(root, 0);

		generateTAC(root);
        // ----------- PRINT TAC -----------
        printf("\nThree Address Code:\n");
        for(int i=0;i<tacIndex;i++) {
            printf("%s\n", tac[i]);
        }

        // ----------- SAVE TAC TO FILE -----------
        FILE *fp = fopen("tac.txt", "w");
        if(fp == NULL) {
            printf("Error opening file!\n");
            return 1;
        }

        for(int i=0;i<tacIndex;i++) {
            fprintf(fp, "%s\n", tac[i]);
        }

        fclose(fp);

        printf("\nTAC saved to tac.txt\n");
    }
    else
    {
        printf("\nParsing Failed\n");
        display();
    }

    fclose(yyin);
    return 0;
}


int yyerror(char *s)
{
    printf("\nLine %d : %s %s\n",yylineno,s,yytext);
	return 0;
}

int printline()
{
	return yylineno;
}
void push()
{
	stack[top]=i;
	i++;
	top++;
	return;
}
void pop()
{
	top--;
	end[stack[top]]=1;
	stack[top]=0;
	return;
}
