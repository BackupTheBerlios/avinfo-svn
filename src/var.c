#include "var.h"

vlist_t* CreateVList(vlist_t* PrevList){
	vlist_t *retval=malloc(sizeof(vlist_t));
	if(retval){
		retval->data=malloc(VARLIST_SIZE*sizeof(vlist_item_t));
		retval->allocated=VARLIST_SIZE;
		if(!retval->data){
		       	free(retval);
			return NULL;
		}
		retval->first_free=0;
		retval->Next=PrevList;
	}
	return retval;

}

void DeleteVList(vlist_t* list){
	int c;
	for(c=0;c<list->first_free;c++){
		if(list->data[c].name) free(list->data[c].name);
		if(list->data[c].string) free(list->data[c].string);
	}
	free(list->data);
	free(list);
}


int SetVar(vlist_t* list,const char* name,const int nvalue, const char* svalue){/*BUG!!!*/
	vlist_item_t *temp;
	int c;
	int result=0;

	for(c=0;c<list->first_free;c++){/*check for existing variable*/
		temp=&(list->data[c]);
		if(temp->name) 
			if(!strcmp(temp->name,name)){
				if(temp->string)free(temp->string);
				goto set;/*found a var.place, go to the VarSetSection*/
			}
	}

	/*we do not found a variable, create new*/
	while(list->first_free>=list->allocated){
		list->allocated*=2;
		assert(list->data=realloc(list->data,list->allocated));/*trap if varlist destroyed*/
	};
	temp=&(list->data[list->first_free]);
	temp->name=strdup(name);
	if(!temp->name) goto ret;
	list->first_free++;
	set:
	temp->number=nvalue;
	if(svalue)assert(temp->string=strdup(svalue));	else temp->string=NULL;
	result=1;
	ret:
	assert(result);
	return result;
}



var_t GetROVar(vlist_t* list, const char* name){
	 vlist_t* p=list;
	 int c;
	 var_t retval={0,NULL};
	 while(p){
		for(c=0;c<p->first_free;c++){
			if(p->data[c].name)
				if(!strcmp(p->data[c].name,name)){
					retval.string=p->data[c].string;
					retval.number=p->data[c].number;
					goto ret;
				}
		}
		p=p->Next;
	}
	ret:
	return retval;
}

int SetStringVar(vlist_t* list,const char* name,const char* svalue){
	return SetVar(list,name,strlen(svalue),strdup(svalue));
}

var_t GetVar(vlist_t* list, const char* name){
	var_t retval=GetROVar(list,name);
	retval.string=strdup(retval.string?retval.string:"");
	return retval;
}


char* GetROStringVar(vlist_t* list,const char* name){

	var_t retval=GetROVar(list,name);
	if(!retval.string) retval.string="";
	return retval.string;
}

int SetIdxVar(vlist_t *list,const char* name, const int param, const int nvalue, const char* svalue){
	char* buffer=malloc(strlen(name)+11);
	int result=0;
	if(buffer){
		sprintf(buffer,name,param);
		result=SetVar(list,buffer,nvalue,svalue);
	}
	free(buffer);
	return result;
}

var_t GetIdxROVar(vlist_t* list, const char* name, const int param){
	var_t retval={0,""};
	char* buffer=malloc(strlen(name)+11);
	if(buffer){
		sprintf(buffer,name,param);
		retval=GetVar(list,buffer);
	}
	free(buffer);
	return retval;
}



void IncStreamCounter( vlist_t* list, int T ){

	char str_type[]	=	"stream.?";
	str_type[7]		=	T;/*setup stream type: T=='a' - str_num=="stream.a", etc */
	SetNumericVar(list,str_type,GetNumericVar(list,str_type)+1);
}


const char *vids_names[VIDEO_INFO_SIZE]={
	"v!.l",
	"v!.x",
	"v!.y",
	"v!.bits",
	"v!.cc",
	"v!.fpsH",
	"v!.fpsL",
	"v!.bps",
	"v!.bspadd",
	"v!.aspectX",
	"v!.aspectY"
};
const char *auds_names[AUDIO_INFO_SIZE]={
	"a!.l",
	"a!.bits",
	"a!.cc",
	"a!.bps",
	"a!.bspadd",
	"a!.ch",
	"a!.freq"
};

void AddAudioVideo(vlist_t* list, unsigned int video[MAX_STREAMS][VIDEO_INFO_SIZE], unsigned int audio[MAX_STREAMS][AUDIO_INFO_SIZE]){
/*TODO: change void to int*/
	unsigned int c;
	unsigned int c2;
	unsigned int a_c=0;
	unsigned int v_c=0;
	char buffer[16];
	for(c=0;c<MAX_STREAMS;c++){
		if(video) if(video[c][V_exist]){
			v_c++;
			for(c2=0;c2<VIDEO_INFO_SIZE-1;c2++){
				if(video[c][c2]){
					strcpy(buffer,vids_names[c2]);
					buffer[1]=v_c+'0';
					if(video[c][c2])SetNumericVar(list,buffer,video[c][c2]);
				}
			}
		}
		if(audio) if(audio[c][A_exist]){
			a_c++;
			for(c2=0;c2<AUDIO_INFO_SIZE-1;c2++){
				if(audio[c][c2]){
					strcpy(buffer,auds_names[c2]);
					buffer[1]=a_c+'0';
					if(audio[c][c2])SetNumericVar(list,buffer,audio[c][c2]);
				}
			}
		}
	}
	SetNumericVar(list,"stream.v",v_c);
	SetNumericVar(list,"stream.a",a_c);

}


void PrintVList(FILE* out,vlist_t* list){
/*
 *	Used for debug purposes
 *	just print to strerr list of variables
 * 
 */
	int c=0;
	for(c=0;c < list->first_free; c++){
			fprintf(out,"%-16s = \t",list->data[c].name);
			if(list->data[c].string) {
				if(list->data[c].string[0]) {
					fprintf(out,"%s\n",list->data[c].string);
					continue;
				}
			}	
			fprintf(out,"%d\n",list->data[c].number);
	}
}

void ViewAllLists(vlist_t* start){
	vlist_t* p=start;
	int c=0;
	while(p){
		printf("list #%d\n",c++);
		PrintVList(stdout,p);
		p=p->Next;
	}
	printf("-----end--\n");
}

void GetMinMaxVarValueByMaskName(vlist_t* list, char* mask, int *min, int *max){
	int c;
	*min=0;
	*max=0;
	for(c=0;c<list->first_free;c++){
		if(!maskstrcmp(list->data[c].name,mask)){
			if(*min==0||(list->data[c].number && *min > list->data[c].number)) *min=list->data[c].number;
			if(*max < list->data[c].number) *max=list->data[c].number;
		}
	}
}

void AddList(vlist_t* to, vlist_t* newlist){
	vlist_t *p=to;
	while(p->Next)	
		p=p->Next;
	p->Next=newlist;
}
