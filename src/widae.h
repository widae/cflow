#include <stdio.h>
#include <list.c>
#include <stack.c>

typedef struct {
        int first;
        int last;
        char head[100];
        //   = if(a == 2)
        int lev;
        int used;
} CS;
//= condition statement

list mylist;
Stack st;

int ind = 0;
int lev = 0;
int reduceAmount = 0;

void setFirst(char * head){

	static int init = 0;

        if(init == 0){
                init_list(&mylist, sizeof(CS));
		init = 1;
	}

	CS cs;

	cs.first = ind;
	cs.last = -1;
	cs.lev = ++lev;
        strncpy(cs.head, head, sizeof(cs.head));
	
	push_back(&mylist, &cs);

        ind++;

}

void setLast(){
        int tmp = -1;
        int i;
        for(i = 0; i < mylist.size; i++){
		CS * ptr = (CS*)get_idx(&mylist, i);
                if(ptr->last == -1){
                        tmp = i;
                }
        }
        if(tmp != -1){
		CS * ptr = (CS*)get_idx(&mylist, tmp);
                ptr->last = ind;
                ind++;
        }
}

int isKeyword(int type, char * token){

	int next = 0;

        if(type == 257){
                if(!strcmp(token, "if") || !strcmp(token, "for") || !strcmp(token, "while") || !strcmp(token, "switch")){
                        setFirst(token);
			next = 1;
                }else if(!strcmp(token, "else") || !strcmp(token, "do")){
                        setFirst(token);
			next = 2;
                }
        }
        return next;
}

void accumulate(int type, char * token){

	int cur = mylist.size - 1;
	CS * ptr = (CS*)get_idx(&mylist, cur);

	if( 0 <= type && type <= 127){
        	sprintf(ptr->head, "%s%c", ptr->head, type);
        }else{
                sprintf(ptr->head, "%s%s", ptr->head, token);
        }

}

int lastRBracket(int type, char * token){

        static int parenLev = 0;

	int next = 1;

	accumulate(type, token);	

	if(type == '('){
        	parenLev++;
        }else if(type == ')'){
                parenLev--;
                if(parenLev == 0){
                	next = 2;
                }
        }

	return next;

}

int checkUsedLBrace(int type, char * token){

        static int step = 0;
        static int parenLev = 0;

        if(step == 0){
                step = isKeyword(type, token);
        }else if(step == 1){
		step = lastRBracket(type, token);	
        }else{
                step = isKeyword(type, token);
                if(type == '{'){
                        return 1;
                }else{
                        return 0;
                }
        }

        return -1;
        //     = don't know yet

}

void setReduceAmount(int type, char * token){
	int usedLBrace = checkUsedLBrace(type, token);
	if(usedLBrace == 1){
		reduceAmount++;
		stack_push(&st, reduceAmount);
		reduceAmount = 0;
	}else if(usedLBrace == 0){
		reduceAmount++;
	}
}

void setLev(int type, char * str){

	static int first = 1;
	if(first == 1){
		stack_init(&st);
		first = 0;
	}

	setReduceAmount(type, str);

        if(lev > 0 && type == '}'){
                int i;
		int tmp = stack_top(&st);
		stack_pop(&st);
                lev -= tmp;
                for(i = 0; i < tmp; i++){
                        setLast();
                }
        }else if(lev > 0 && type == ';'){
                int i;
                lev -= reduceAmount;
                for(i = 0; i < reduceAmount; i++){
                        setLast();
                }
                reduceAmount = 0;
        }

}

void indent(int lev, FILE * outfile){
	int i;
	for(i = 0; i < lev; i++){
		fprintf(outfile, "    ");
	}
}

void printTail(int i, int doLev){
	int j;
	for(j = i+1; j < mylist.size; j++){
		CS * ptr = (CS*)get_idx(&mylist, j);
		if(ptr->lev == doLev){
                	fprintf(outfile, "/%s", ptr->head);
			break;
		}
	}
}

void printHead(int * callerLev, struct output_symbol * s){
	Symbol * sym = s->sym;
        int i;
        for(i = 0; i < mylist.size; i++){
		CS * ptr = (CS*)get_idx(&mylist, i);
		if(ptr->used == 0){
        		if(ptr->first < sym->index && sym->index < ptr->last){
				indent(callerLev[s->level] + ptr->lev, outfile);	
                		fprintf(outfile, "%s", ptr->head);
				if(!strcmp(ptr->head, "do")){
					printTail(i, ptr->lev);
				}
				fprintf(outfile, "\n");
				ptr->used = 1;
                	}
		}
        }
}

void initUsed(){
	int i;
	for(i = 0; i < mylist.size; i++){
		CS * ptr = (CS*)get_idx(&mylist, i);
		ptr->used = 0;
	}
}

void setCallerLev(int * callerLev, int originLev, int symLev){
	int cur = originLev;
        int next = cur + 1;
	if(originLev == 0 && symLev == 0){
		callerLev[next] = callerLev[cur] + symLev;
	}else{
		callerLev[next] = callerLev[cur] + symLev + 1;
		indent(callerLev[cur] + symLev + 1, outfile);
	}
}		








