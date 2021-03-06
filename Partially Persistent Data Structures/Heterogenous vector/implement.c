#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"

het_Node* int_addNode(int data)
{
  het_Node* newnode = (het_Node*) malloc(sizeof(het_Node));
  
  newnode->int_data = data;
  newnode->float_data = JUNK;
  newnode->char_data = JUNK;
  newnode->double_data = JUNK;
 
  newnode->identifier = "int";
  newnode->next = NULL;
  newnode->prev = NULL;
	
  newnode->mod = (het_Mod*) malloc(sizeof(het_Mod));
  newnode->mod->int_data = JUNK;
  newnode->mod->float_data = JUNK;
  newnode->mod->char_data = JUNK;
  newnode->mod->double_data = JUNK;
  
  newnode->mod->version = UNUSED;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
	
  return newnode;
}


het_Node* float_addNode(float data)
{
  het_Node* newnode = (het_Node*) malloc(sizeof(het_Node));
  
  newnode->int_data = JUNK;
  newnode->float_data = data;
  newnode->char_data = JUNK;
  newnode->double_data = JUNK;
 
  newnode->identifier = "float";
  newnode->next = NULL;
  newnode->prev = NULL;
	
  newnode->mod = (het_Mod*) malloc(sizeof(het_Mod));
  newnode->mod->int_data = JUNK;
  newnode->mod->float_data = JUNK;
  newnode->mod->char_data = JUNK;
  newnode->mod->double_data = JUNK;
  
  newnode->mod->version = UNUSED;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
	
  return newnode;
}


het_Node* char_addNode(char data)
{
  het_Node* newnode = (het_Node*) malloc(sizeof(het_Node));
  
  newnode->int_data = JUNK;
  newnode->float_data = JUNK;
  newnode->char_data = data;
  newnode->double_data = JUNK;

  newnode->identifier = "char";
  newnode->next = NULL;
  newnode->prev = NULL;
	
  newnode->mod = (het_Mod*) malloc(sizeof(het_Mod));
  newnode->mod->int_data = JUNK;
  newnode->mod->float_data = JUNK;
  newnode->mod->char_data = JUNK;
  newnode->mod->double_data = JUNK;
  
  newnode->mod->version = UNUSED;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
	
  return newnode;
}


het_Node* double_addNode(double data)
{
  het_Node* newnode = (het_Node*) malloc(sizeof(het_Node));
  
  newnode->int_data = JUNK;
  newnode->float_data = JUNK;
  newnode->char_data = JUNK;
  newnode->double_data = data;
  
  newnode->identifier = "double";
  newnode->next = NULL;
  newnode->prev = NULL;
	
  newnode->mod = (het_Mod*) malloc(sizeof(het_Mod));
  newnode->mod->int_data = JUNK;
  newnode->mod->float_data = JUNK;
  newnode->mod->char_data = JUNK;
  newnode->mod->double_data = JUNK;
  newnode->mod->version = UNUSED;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
	
  return newnode;
}



het_list_pp* het_init_list_pp()
{
  het_list_pp* newlist = (het_list_pp*) malloc(sizeof(het_list_pp));

  if(!newlist)
    {
      printf("Error in list creation\n");
      return NULL;
    }

  newlist->live_version = 0;

  for(int i = 0; i < MAX_OP; i++)
    newlist->head[i] = NULL;
      
  return newlist;
}



void het_print_list_pp(het_list_pp* list, int version)
{
  if(list->live_version < version)
    {
      printf("Entered version does not exist\n");
      return;
    }
  
  het_Node* pCrawl = (het_Node*) malloc(sizeof(het_Node));

  printf("List of version %d\n", version);
	
  if(!pCrawl)	
    {
      printf("Memory allocation error");
      return;
    }

  for(pCrawl = list->head[version]; pCrawl != NULL; )
    {
      if((pCrawl->mod->version <= version) && (pCrawl->mod->version != UNUSED))
	{
	  switch(pCrawl->mod->identifier[0])
	    {
	    case 'i': {
	      printf("%d->", pCrawl->mod->int_data);
	      pCrawl = pCrawl->mod->next;
	      break;
	    }
	    case 'f' : {
	      printf("%f->", pCrawl->mod->float_data);
	      pCrawl = pCrawl->mod->next;
	      break;
	    }
	    case 'c': {
	      printf("%c->", pCrawl->mod->char_data);
	      pCrawl = pCrawl->mod->next;
	      break;
	    }
	    case 'd':{
	      printf("%lf->", pCrawl->mod->double_data);
	      pCrawl = pCrawl->mod->next;
	      break;
	    }
	    default :{
	      pCrawl = pCrawl->mod->next;
	    }
	    }
	}
      else
	{
	  switch(pCrawl->identifier[0])
	    {
	    case 'i': {
	      printf("%d->", pCrawl->int_data);
	      pCrawl = pCrawl->next;
	      break;
	    }
	    case 'f' : {
	      printf("%f->", pCrawl->float_data);
	      pCrawl = pCrawl->next;
	      break;
	    }
	    case 'c': {
	      printf("%c->", pCrawl->char_data);
	      pCrawl = pCrawl->next;
	      break;
	    }
	    case 'd':{
	      printf("%lf->", pCrawl->double_data);
	      pCrawl = pCrawl->next;
	      break;
	    }
	    default :{
	      pCrawl = pCrawl->next;
	    }
	    }
	}
    }
  printf("NULL\n");
}


het_Node* het_update_parentLeft_list_pp(het_list_pp* list, het_Node* lCrawl, het_Node* newnode, int live_version)
{

  if(lCrawl == NULL) return NULL;

  if(lCrawl->mod->version == UNUSED)
    {
      switch(lCrawl->identifier[0])
	{
	case 'i': {
	  lCrawl->mod->int_data = lCrawl->int_data;
	  lCrawl->mod->identifier = "int";
	  break;
	}
	case 'f': {
	  lCrawl->mod->float_data = lCrawl->float_data;
	  lCrawl->mod->identifier = "float";
	  break;
	}
	case 'c': {
	  lCrawl->mod->char_data = lCrawl->char_data;
	  lCrawl->mod->identifier = "char";
	  break;
	}
	case 'd': {
	  lCrawl->mod->double_data = lCrawl->double_data;
	  lCrawl->mod->identifier = "double";
	  break;
	}
	default: {
	  ;
	}
	}

      lCrawl->mod->version = live_version;
      lCrawl->mod->next = newnode;
      lCrawl->mod->prev = lCrawl->prev;

      list->head[live_version] = list->head[live_version-1];
      return lCrawl;
    }
  else
    {
      het_Node* newnode_parent;
      switch(lCrawl->mod->identifier[0])
	{
	case 'i': {
	  newnode_parent = int_addNode(lCrawl->mod->int_data);
	  break;
	}
	case 'f': {
	  newnode_parent = float_addNode(lCrawl->mod->float_data);
	  break;
	}
	case 'c': {
	  newnode_parent = char_addNode(lCrawl->mod->char_data);
	  break;
	}
	case 'd': {
	  newnode_parent = double_addNode(lCrawl->mod->double_data);
	  break;
	}
	default: {
	  ;
	}
	}
       
      newnode_parent->next = newnode;

      if(lCrawl->mod->prev == NULL)
	{
	  list->head[live_version] = newnode_parent;
	  return newnode_parent;
	}
      
      newnode_parent->prev = het_update_parentLeft_list_pp(list, lCrawl->mod->prev, newnode_parent, live_version);
      return newnode_parent;
    }
}



het_Node* het_update_parentRight_list_pp(het_list_pp* list, het_Node* lCrawl, het_Node* newnode, int live_version)
{

  if(lCrawl == NULL) return NULL;
    
  if(lCrawl->mod->version == UNUSED)
    {
      switch(lCrawl->identifier[0])
	{
	case 'i': {
	  lCrawl->mod->int_data = lCrawl->int_data;
	  lCrawl->mod->identifier = "int";
	  break;
	}
	case 'f': {
	  lCrawl->mod->float_data = lCrawl->float_data;
	  lCrawl->mod->identifier = "float";
	  break;
	}
	case 'c': {
	  lCrawl->mod->char_data = lCrawl->char_data;
	  lCrawl->mod->identifier = "char";
	  break;
	}
	case 'd': {
	  lCrawl->mod->double_data = lCrawl->double_data;
	  lCrawl->mod->identifier = "double";
	  break;
	}
	default: {
	  ;
	}
	}

      lCrawl->mod->version = live_version;
      lCrawl->mod->prev = newnode;
      lCrawl->mod->next = lCrawl->next;

      return lCrawl;
    }
  else
    {
      het_Node* newnode_parent;
      switch(lCrawl->mod->identifier[0])
	{
	case 'i': {
	  newnode_parent = int_addNode(lCrawl->mod->int_data);
	  break;
	}
	case 'f': {
	  newnode_parent = float_addNode(lCrawl->mod->float_data);
	  break;
	}
	case 'c': {
	  newnode_parent = char_addNode(lCrawl->mod->char_data);
	  break;
	}
	case 'd': {
	  newnode_parent = double_addNode(lCrawl->mod->double_data);
	  break;
	}
	default: {
	  ;
	}
	}

      newnode_parent->prev = newnode;
	
      newnode_parent->next = het_update_parentRight_list_pp(list, lCrawl->mod->next, newnode_parent, live_version);
      return newnode_parent;
    }
}



bool het_insert_list_pp(het_list_pp* list, char str[], int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
  
  int index_count = 0;
  int live_version = list->live_version;

  het_Node* newnode;
  switch(str[0])
    {
    case 'i': {
      int int_data;
      sscanf(str, "%*[^','],%d", &int_data);
      newnode = int_addNode(int_data);
      break;
    }
    case 'f': {
      float float_data;
      sscanf(str, "%*[^','],%f", &float_data);
      newnode = float_addNode(float_data);
      break;
    }
    case 'c': {
      char char_data;
      sscanf(str, "%*[^','],%c", &char_data);
      newnode = char_addNode(char_data);
      break;
    }
    case 'd': {
      double double_data;
      sscanf(str, "%*[^','],%lf", &double_data);
      newnode = double_addNode(double_data);
      break;
    }
    default: {
      printf("Invalid datatype\n");
    }
    }  
  
  het_Node* lCrawl = (het_Node*) malloc(sizeof(het_Node));
  het_Node* lCrawl_prev = (het_Node*) malloc(sizeof(het_Node));
  
  if(!lCrawl)	
    {
      printf("Memory allocation error");
      return false;
    }
  
  if(!lCrawl_prev)	
    {
      printf("Memory allocation error");
      return false;
    }
 
  for(lCrawl = list->head[live_version], lCrawl_prev = list->head[live_version]; lCrawl != NULL; index_count++)
    {
      if(lCrawl != list->head[live_version])
	lCrawl_prev = lCrawl->prev;
      
      if(index_count == index) break;
      
      if((lCrawl->mod->version <= live_version) && lCrawl->mod->version != UNUSED)
	lCrawl = lCrawl->mod->next;
      else
	lCrawl = lCrawl->next;
    }
  
  if(list->head[live_version] == NULL)
    {
      list->head[live_version] = newnode;
      return true;
    }
  if(lCrawl == NULL) index_count--;
  
  if(index != index_count) 
    {
      printf("Index greater than length of the list. The element will be appended at the end of the list\n");
    }
  
  if(lCrawl_prev == list->head[live_version] && index == 1)
    lCrawl = lCrawl_prev;
  else if((lCrawl == NULL) && (lCrawl_prev->mod->version == UNUSED))
    lCrawl = lCrawl_prev->next;
  else if((lCrawl == NULL) && (lCrawl_prev->mod->version != UNUSED))
    lCrawl = lCrawl_prev->mod->next;
  else
    lCrawl = lCrawl_prev;  

  if(lCrawl->mod->version == UNUSED)
    {      
      live_version++;

      switch(lCrawl->identifier[0])
	{
	case 'i': {
	  lCrawl->mod->int_data = lCrawl->int_data;
	  lCrawl->mod->identifier = "int";
	  break;
	}
	case 'f': {
	  lCrawl->mod->float_data = lCrawl->float_data;
	  lCrawl->mod->identifier = "float";
	  break;
	}
	case 'c': {
	  lCrawl->mod->char_data = lCrawl->char_data;
	  lCrawl->mod->identifier = "char";
	  break;
	}
	case 'd': {
	  lCrawl->mod->double_data = lCrawl->double_data;
	  lCrawl->mod->identifier = "double";
	  break;
	}
	default: {
	  ;
	}
	}

      lCrawl->mod->version = live_version;

      if(index != 0)
	{
	  lCrawl->mod->next = newnode;
	  lCrawl->mod->prev = lCrawl->prev;

	  newnode->next = het_update_parentRight_list_pp(list, lCrawl->next, newnode, live_version);
	  newnode->prev = het_update_parentLeft_list_pp(list, lCrawl, newnode, live_version);
	}
      else
	{
	  newnode->next = lCrawl;
  	  lCrawl->mod->next = lCrawl->next;
	  lCrawl->mod->prev = newnode;

	  list->head[live_version] = newnode;
      	}
    }
  else
    {
      live_version++;
   
      if(index !=0)
	{
	  newnode->next = het_update_parentRight_list_pp(list, lCrawl->mod->next, newnode, live_version);
	  newnode->prev = het_update_parentLeft_list_pp(list, lCrawl, newnode, live_version);
	}
      else
	{
	  het_Node* trailNode;
	  switch(lCrawl->mod->identifier[0])
	    {
	    case 'i': {
	      trailNode = int_addNode(lCrawl->mod->int_data);
	      break;
	    }
	    case 'f': {
	      trailNode = float_addNode(lCrawl->mod->float_data);
	      break;
	    }
	    case 'c': {
	      trailNode = char_addNode(lCrawl->mod->char_data);
	      break;
	    }
	    case 'd': {
	      trailNode = double_addNode(lCrawl->mod->double_data);
	      break;
	    }
	    default: {
	      ;
	    }
	    }

	  trailNode->next = lCrawl->mod->next;
	  trailNode->prev = newnode;
	  
	  newnode->next = trailNode;
  	  
	  list->head[live_version] = newnode;
	}
    }
  
  list->live_version = live_version;
  return true;
}



bool het_update_list_pp(het_list_pp* list, char str[], int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
  
  int index_count = 0;
  int live_version = list->live_version;

  het_Node* lCrawl = (het_Node*) malloc(sizeof(het_Node));
  
  if(!lCrawl)	
    {
      printf("Memory allocation error");
      return false;
    }
 
  for(lCrawl = list->head[live_version]; lCrawl != NULL; index_count++)
    {
      if(index_count == index) break;
      
      if((lCrawl->mod->version <= live_version) && lCrawl->mod->version != UNUSED)
	lCrawl = lCrawl->mod->next;
      else
	lCrawl = lCrawl->next;
    }
  
  if(lCrawl == NULL) index_count--;
  
  if(index != index_count) 
    {
      printf("Index not found in the list. ");
      het_insert_list_pp(list, str, index);
    }
  else
    {
      char type[STR_SIZE];
      
      if(lCrawl->mod->version == UNUSED)
	{  
	  live_version++;

	  switch(str[0])
	    {
	    case 'i': {
	      int int_data;
	      sscanf(str, "%*[^','],%d", &int_data);
	      lCrawl->mod->int_data = int_data;
	      lCrawl->mod->identifier = "int";
	      break;
	    }
	    case 'f': {
	      float float_data;
	      sscanf(str, "%*[^','],%f", &float_data);
	      lCrawl->mod->float_data = float_data;
	      lCrawl->mod->identifier = "float";
	      break;
	    }
	    case 'c': {
	      char char_data;
	      sscanf(str, "%*[^','],%c", &char_data);
	      lCrawl->mod->char_data = char_data;
	      lCrawl->mod->identifier = "char";
	      break;
	    }
	    case 'd': {
	      double double_data;
	      sscanf(str, "%*[^','],%lf", &double_data);
	      lCrawl->mod->double_data = double_data;
	      lCrawl->mod->identifier = "double";
	      break;
	    }
	    default: {
	      ;
	    }
	    }

	  lCrawl->mod->version = live_version;
	  lCrawl->mod->next = lCrawl->next;
	  lCrawl->mod->prev = lCrawl->prev;

	  list->head[live_version] = list->head[live_version-1];
	}
      else
	{
	  live_version++;	  
	  het_Node* newnode;
	  
	  switch(str[0])
	    {
	    case 'i': {
	      int int_data;
	      sscanf(str, "%*[^','],%d", &int_data);
	      newnode = int_addNode(int_data);
	      break;
	    }
	    case 'f': {
	      float float_data;
	      sscanf(str, "%*[^','],%f", &float_data);
	      newnode = float_addNode(float_data);
	      break;
	    }
	    case 'c': {
	      char char_data;
	      sscanf(str, "%*[^','],%c", &char_data); 
	      newnode = char_addNode(char_data);
	      break;
	    }
	    case 'd': {
	      double double_data;
	      sscanf(str, "%*[^','],%lf", &double_data);
	      newnode = double_addNode(double_data);
	      break;
	    }
	    default: {
	      printf("Invalid datatype\n");
	    }
	    }  
  
	  
	  if(index != 0)
	    {
	      newnode->next = het_update_parentRight_list_pp(list, lCrawl->mod->next, newnode, live_version);
	      newnode->prev = het_update_parentLeft_list_pp(list, lCrawl->mod->prev, newnode, live_version);
	    }
	  else
	    {	  
	      newnode->next = het_update_parentRight_list_pp(list, lCrawl->mod->next, newnode, live_version);
	      list->head[live_version] = newnode;
	    }
	}

      list->live_version = live_version;
    }
  return true;
}




bool het_delete_list_pp(het_list_pp* list, int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
      
  int index_count = 0;
  int live_version = list->live_version;

  het_Node* lCrawl = (het_Node*) malloc(sizeof(het_Node));
  
  if(!lCrawl)	
    {
      printf("Memory allocation error");
      return false;
    }
  
  if(list->head[live_version] == NULL)
    {
      printf("List is empty. Cannot delete from empty list");
      return false;
    }
  
  if(list->head[live_version]->next == NULL)
    {
      live_version++;
      list->head[live_version] = NULL;
       
      list->live_version = live_version;
      return true;
    }
  
  for(lCrawl = list->head[live_version]; lCrawl != NULL; index_count++)
    {
      if(index_count == index) break;
      
      if((lCrawl->mod->version <= live_version) && lCrawl->mod->version != UNUSED)
	lCrawl = lCrawl->mod->next;
      else
	lCrawl = lCrawl->next;
    }
  
  if(lCrawl == NULL) index_count--;

  if(index != index_count) 
    {
      printf("Index not found in the list\n");
      return false;
    }
  else
    {
      if(index == 0)
	{
	  if(lCrawl->mod->version == UNUSED)
	    {
	      if(lCrawl->next->mod->version == UNUSED)
		{  
		  live_version++;
	
		  switch(lCrawl->next->identifier[0])
		    {
		    case 'i': {
		      lCrawl->next->mod->int_data = lCrawl->next->int_data;
		      lCrawl->next->mod->identifier = "int";
		      break;
		    }
		    case 'f': {
		      lCrawl->next->mod->float_data = lCrawl->next->float_data;
		      lCrawl->next->mod->identifier = "float";
		      break;
		    }
		    case 'c': {
		      lCrawl->next->mod->char_data = lCrawl->next->char_data;
		      lCrawl->next->mod->identifier = "char";
		      break;
		    }
		    case 'd': {
		      lCrawl->next->mod->double_data = lCrawl->next->double_data;
		      lCrawl->next->mod->identifier = "double";
		      break;
		    }
		    default: {
		      ;
		    }
		    }

		  lCrawl->next->mod->version = live_version;
		  lCrawl->next->mod->next = lCrawl->next->next;
		  lCrawl->next->mod->prev = lCrawl->prev;

		  list->head[live_version] = lCrawl->next;
		}
	      else
		{
		  live_version++;
		  het_Node* newnode;
		  
		  switch(lCrawl->next->mod->identifier[0])
		    {
		    case 'i': {
		      newnode = int_addNode(lCrawl->next->mod->int_data);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(lCrawl->next->mod->float_data);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(lCrawl->next->mod->char_data);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(lCrawl->next->mod->double_data);
		      break;
		    }
		    default: {
		      ;
		    }
		    }

		  newnode->next = het_update_parentRight_list_pp(list, lCrawl->next->mod->next, newnode, live_version);
	  	  
		  list->head[live_version] = newnode;
		}
	    }
	  else
	    {
	      if(lCrawl->mod->next->mod->version == UNUSED)
		{  
		  live_version++;

		  switch(lCrawl->mod->next->identifier[0])
		    {
		    case 'i': {
		      lCrawl->mod->next->mod->int_data = lCrawl->mod->next->int_data;
		      lCrawl->mod->next->mod->identifier = "int";
		      break;
		    }
		    case 'f': {
		      lCrawl->mod->next->mod->float_data = lCrawl->mod->next->float_data;
		      lCrawl->mod->next->mod->identifier = "float";
		      break;
		    }
		    case 'c': {
		      lCrawl->mod->next->mod->char_data = lCrawl->mod->next->char_data;
		      lCrawl->mod->next->mod->identifier = "char";
		      break;
		    }
		    case 'd': {
		      lCrawl->mod->next->mod->double_data = lCrawl->mod->next->double_data;
		      lCrawl->mod->next->mod->identifier = "double";
		      break;
		    }
		    default: {
		      ;
		    }
		    }

		  lCrawl->mod->next->mod->version = live_version;
		  lCrawl->mod->next->mod->next = lCrawl->mod->next->next;
		  lCrawl->mod->next->mod->prev = lCrawl->mod->prev;

		  list->head[live_version] = lCrawl->mod->next;
		}
	      else
		{
		  live_version++;
		  het_Node* newnode;
		  
		  switch(lCrawl->mod->next->mod->identifier[0])
		    {
		    case 'i': {
		      newnode = int_addNode(lCrawl->mod->next->mod->int_data);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(lCrawl->mod->next->mod->float_data);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(lCrawl->mod->next->mod->char_data);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(lCrawl->mod->next->mod->double_data);
		      break;
		    }
		    default: {
		      ;
		    }
		    }

		  newnode->next = het_update_parentRight_list_pp(list, lCrawl->mod->next->mod->next, newnode, live_version);
	  	  
		  list->head[live_version] = newnode;
		}
	    }
	  
	  list->live_version = live_version;
	  return true;
	}

      if((lCrawl->next == NULL) && (lCrawl->mod->version == UNUSED))
	{
	  if(lCrawl->prev->mod->version == UNUSED)
	    {  
	      live_version++;

	      switch(lCrawl->prev->identifier[0])
		{
		case 'i': {
		  lCrawl->prev->mod->int_data = lCrawl->prev->int_data;
		  lCrawl->prev->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  lCrawl->prev->mod->float_data = lCrawl->prev->float_data;
		  lCrawl->prev->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  lCrawl->prev->mod->char_data = lCrawl->prev->char_data;
		  lCrawl->prev->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  lCrawl->prev->mod->double_data = lCrawl->prev->double_data;
		  lCrawl->prev->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}
 
	      lCrawl->prev->mod->version = live_version;
	      lCrawl->prev->mod->next = lCrawl->next;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      list->head[live_version] = list->head[live_version-1];
	    }
	  else
	    {
	      live_version++;
	      het_Node* newnode;
	      
	      switch(lCrawl->prev->mod->identifier[0])
		{
		case 'i': {
		  newnode = int_addNode(lCrawl->prev->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode = float_addNode(lCrawl->prev->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode = char_addNode(lCrawl->prev->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode = double_addNode(lCrawl->prev->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}
	      
	      newnode->prev = het_update_parentLeft_list_pp(list, lCrawl->prev->mod->prev, newnode, live_version);
	    }
 
	  list->live_version = live_version;
	  return true;
	}
      
      if((lCrawl->mod->next == NULL) && (lCrawl->mod->version != UNUSED))
	{
	  if(lCrawl->mod->prev->mod->version == UNUSED)
	    {  
	      live_version++;

	      switch(lCrawl->mod->prev->identifier[0])
		{
		case 'i': {
		  lCrawl->mod->prev->mod->int_data = lCrawl->mod->prev->int_data;
		  lCrawl->mod->prev->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  lCrawl->mod->prev->mod->float_data = lCrawl->mod->prev->float_data;
		  lCrawl->mod->prev->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  lCrawl->mod->prev->mod->char_data = lCrawl->mod->prev->char_data;
		  lCrawl->mod->prev->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  lCrawl->mod->prev->mod->double_data = lCrawl->mod->prev->double_data;
		  lCrawl->mod->prev->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}
	      
	      lCrawl->mod->prev->mod->version = live_version;
	      lCrawl->mod->prev->mod->next = lCrawl->mod->next;
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;

	      list->head[live_version] = list->head[live_version-1];
	    }
	  else
	    {
	      live_version++;
	      het_Node* newnode;
	      
	      switch(lCrawl->mod->prev->mod->identifier[0])
		{
		case 'i': {
		  newnode = int_addNode(lCrawl->mod->prev->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode = float_addNode(lCrawl->mod->prev->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode = char_addNode(lCrawl->mod->prev->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode = double_addNode(lCrawl->mod->prev->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}
	      	      
	      newnode->prev = het_update_parentLeft_list_pp(list, lCrawl->mod->prev->mod->prev, newnode, live_version);
	    }

	  list->live_version = live_version;
	  return true;
	}
      

      if(lCrawl->mod->version == UNUSED)
	{
	  if((lCrawl->prev->mod->version == UNUSED) && (lCrawl->next->mod->version == UNUSED))
	    {  
	      live_version++;

	      switch(lCrawl->prev->identifier[0])
		{
		case 'i': {
		  lCrawl->prev->mod->int_data = lCrawl->prev->int_data;
		  lCrawl->prev->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  lCrawl->prev->mod->float_data = lCrawl->prev->float_data;
		  lCrawl->prev->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  lCrawl->prev->mod->char_data = lCrawl->prev->char_data;
		  lCrawl->prev->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  lCrawl->prev->mod->double_data = lCrawl->prev->double_data;
		  lCrawl->prev->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}

	      lCrawl->prev->mod->version = live_version;
	      lCrawl->prev->mod->next = lCrawl->next;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      switch(lCrawl->next->identifier[0])
		{
		case 'i': {
		  lCrawl->next->mod->int_data = lCrawl->next->int_data;
		  lCrawl->next->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  lCrawl->next->mod->float_data = lCrawl->next->float_data;
		  lCrawl->next->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  lCrawl->next->mod->char_data = lCrawl->next->char_data;
		  lCrawl->next->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  lCrawl->next->mod->double_data = lCrawl->next->double_data;
		  lCrawl->next->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}

	      lCrawl->next->mod->version = live_version;
	      lCrawl->next->mod->next = lCrawl->next->next;
	      lCrawl->next->mod->prev = lCrawl->prev;

	      list->head[live_version] = list->head[live_version-1];
	    }
	  else if((lCrawl->prev->mod->version == UNUSED) && (lCrawl->next->mod->version != UNUSED))
	    {
	      live_version++;
	      
	      switch(lCrawl->prev->identifier[0])
		{
		case 'i': {
		  lCrawl->prev->mod->int_data = lCrawl->prev->int_data;
		  lCrawl->prev->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  lCrawl->prev->mod->float_data = lCrawl->prev->float_data;
		  lCrawl->prev->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  lCrawl->prev->mod->char_data = lCrawl->prev->char_data;
		  lCrawl->prev->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  lCrawl->prev->mod->double_data = lCrawl->prev->double_data;
		  lCrawl->prev->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}
	      
	      het_Node* newnode;
	      switch(lCrawl->next->mod->identifier[0])
		{
		case 'i': {
		  newnode = int_addNode(lCrawl->next->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode = float_addNode(lCrawl->next->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode = char_addNode(lCrawl->next->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode = double_addNode(lCrawl->next->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}
	      
	      lCrawl->prev->mod->version = live_version;

	      lCrawl->prev->mod->next = newnode;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      newnode->prev = lCrawl->prev;		
	      newnode->next = het_update_parentRight_list_pp(list, lCrawl->next->mod->next, newnode, live_version);
	  	  
	      list->head[live_version] = list->head[live_version-1];
	    }
	  else if((lCrawl->prev->mod->version != UNUSED) && (lCrawl->next->mod->version == UNUSED))
	    {
	      live_version++;
	      het_Node* newnode;
	      
	      switch(lCrawl->prev->mod->identifier[0])
		{
		case 'i': {
		  newnode = int_addNode(lCrawl->prev->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode = float_addNode(lCrawl->prev->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode = char_addNode(lCrawl->prev->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode = double_addNode(lCrawl->prev->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}

	      switch(lCrawl->next->identifier[0])
		{
		case 'i': {
		  lCrawl->next->mod->int_data = lCrawl->next->int_data;
		  lCrawl->next->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  lCrawl->next->mod->float_data = lCrawl->next->float_data;
		  lCrawl->next->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  lCrawl->next->mod->char_data = lCrawl->next->char_data;
		  lCrawl->next->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  lCrawl->next->mod->double_data = lCrawl->next->double_data;
		  lCrawl->next->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}

	      lCrawl->next->mod->version = live_version;

	      lCrawl->next->mod->next = lCrawl->next->next;
	      lCrawl->next->mod->prev = newnode;

	      newnode->next = lCrawl->next;
	      newnode->prev = het_update_parentLeft_list_pp(list, lCrawl->prev->mod->prev, newnode, live_version);
	    }
	  else
	    {
	      live_version++;        
	      het_Node* newnode_prev;
	      
	      switch(lCrawl->prev->mod->identifier[0])
		{
		case 'i': {
		  newnode_prev = int_addNode(lCrawl->prev->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode_prev = float_addNode(lCrawl->prev->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode_prev = char_addNode(lCrawl->prev->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode_prev = double_addNode(lCrawl->prev->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}

	      het_Node* newnode_next;
	      switch(lCrawl->next->mod->identifier[0])
		{
		case 'i': {
		  newnode_next = int_addNode(lCrawl->next->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode_next = float_addNode(lCrawl->next->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode_next = char_addNode(lCrawl->next->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode_next = double_addNode(lCrawl->next->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}
	      
	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	      newnode_prev->prev = het_update_parentLeft_list_pp(list, lCrawl->prev->mod->prev, newnode_prev, live_version);
	      newnode_next->next = het_update_parentRight_list_pp(list, lCrawl->next->mod->next, newnode_next, live_version);
 	    }
	}
      else
	{
	  if((lCrawl->mod->prev->mod->version == UNUSED) && (lCrawl->mod->next->mod->version == UNUSED))
	    {  
	      live_version++;
	     
	      switch(lCrawl->mod->prev->identifier[0])
		{
		case 'i': {
		  lCrawl->mod->prev->mod->int_data = lCrawl->mod->prev->int_data;
		  lCrawl->mod->prev->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  lCrawl->mod->prev->mod->float_data = lCrawl->mod->prev->float_data;
		  lCrawl->mod->prev->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  lCrawl->mod->prev->mod->char_data = lCrawl->mod->prev->char_data;
		  lCrawl->mod->prev->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  lCrawl->mod->prev->mod->double_data = lCrawl->mod->prev->double_data;
		  lCrawl->mod->prev->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}

	      lCrawl->mod->prev->mod->version = live_version;
	      lCrawl->mod->prev->mod->next = lCrawl->mod->next;
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;

	      switch(lCrawl->mod->next->identifier[0])
		{
		case 'i': {
		  lCrawl->mod->next->mod->int_data = lCrawl->mod->next->int_data;
		  lCrawl->mod->next->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  lCrawl->mod->next->mod->float_data = lCrawl->mod->next->float_data;
		  lCrawl->mod->next->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  lCrawl->mod->next->mod->char_data = lCrawl->mod->next->char_data;
		  lCrawl->mod->next->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  lCrawl->mod->next->mod->double_data = lCrawl->mod->next->double_data;
		  lCrawl->mod->next->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}

	      lCrawl->mod->next->mod->version = live_version;

	      lCrawl->mod->next->mod->next = lCrawl->mod->next->next;
	      lCrawl->mod->next->mod->prev = lCrawl->mod->prev;

	      list->head[live_version] = list->head[live_version-1];
	    }
	  else if((lCrawl->mod->prev->mod->version == UNUSED) && (lCrawl->mod->next->mod->version != UNUSED))
	    {
	      live_version++;
	      
	      switch(lCrawl->mod->prev->identifier[0])
		{
		case 'i': {
		  lCrawl->mod->prev->mod->int_data = lCrawl->mod->prev->int_data;
		  lCrawl->mod->prev->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  lCrawl->mod->prev->mod->float_data = lCrawl->mod->prev->float_data;
		  lCrawl->mod->prev->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  lCrawl->mod->prev->mod->char_data = lCrawl->mod->prev->char_data;
		  lCrawl->mod->prev->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  lCrawl->mod->prev->mod->double_data = lCrawl->mod->prev->double_data;
		  lCrawl->mod->prev->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}
	 
	      het_Node* newnode ;
	      switch(lCrawl->mod->next->mod->identifier[0])
		{
		case 'i': {
		  newnode = int_addNode(lCrawl->mod->next->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode = float_addNode(lCrawl->mod->next->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode = char_addNode(lCrawl->mod->next->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode = double_addNode(lCrawl->mod->next->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}
	      	      
	      lCrawl->mod->prev->mod->version = live_version;

	      lCrawl->mod->prev->mod->next = newnode;
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;
	      
	      newnode->prev = lCrawl->mod->prev;
	      newnode->next = het_update_parentRight_list_pp(list, lCrawl->mod->next->mod->next, newnode, live_version);
	  	  
	      list->head[live_version] = list->head[live_version-1];
	    }
	  else if((lCrawl->mod->prev->mod->version != UNUSED) && (lCrawl->mod->next->mod->version == UNUSED))
	    {
	      live_version++;

	      switch(lCrawl->mod->next->identifier[0])
		{
		case 'i': {
		  lCrawl->mod->next->mod->int_data = lCrawl->mod->next->int_data;
		  lCrawl->mod->next->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  lCrawl->mod->next->mod->float_data = lCrawl->mod->next->float_data;
		  lCrawl->mod->next->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  lCrawl->mod->next->mod->char_data = lCrawl->mod->next->char_data;
		  lCrawl->mod->next->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  lCrawl->mod->next->mod->double_data = lCrawl->mod->next->double_data;
		  lCrawl->mod->next->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}
	      
	      het_Node* newnode;
	      switch(lCrawl->mod->prev->mod->identifier[0])
		{
		case 'i': {
		  newnode = int_addNode(lCrawl->mod->prev->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode = float_addNode(lCrawl->mod->prev->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode = char_addNode(lCrawl->mod->prev->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode = double_addNode(lCrawl->mod->prev->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}
	     
	      lCrawl->mod->next->mod->version = live_version;

	      lCrawl->mod->next->mod->next = lCrawl->mod->next->next;
	      lCrawl->mod->next->mod->prev = newnode;

	      newnode->next = lCrawl->mod->next;

	      newnode->prev = het_update_parentLeft_list_pp(list, lCrawl->mod->prev->mod->prev, newnode, live_version);
	    }
	  else
	    {
	      live_version++;
	      het_Node* newnode_prev;
	      
	      switch(lCrawl->mod->prev->mod->identifier[0])
		{
		case 'i': {
		  newnode_prev = int_addNode(lCrawl->mod->prev->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode_prev = float_addNode(lCrawl->mod->prev->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode_prev = char_addNode(lCrawl->mod->prev->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode_prev = double_addNode(lCrawl->mod->prev->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}

	      het_Node* newnode_next;
	      switch(lCrawl->mod->next->mod->identifier[0])
		{
		case 'i': {
		  newnode_next = int_addNode(lCrawl->mod->next->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode_next = float_addNode(lCrawl->mod->next->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode_next = char_addNode(lCrawl->mod->next->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode_next = double_addNode(lCrawl->mod->next->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}	      

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	      newnode_prev->prev = het_update_parentLeft_list_pp(list, lCrawl->mod->prev->mod->prev, newnode_prev, live_version);
	      newnode_next->next = het_update_parentRight_list_pp(list, lCrawl->mod->next->mod->next, newnode_next, live_version);
	    }

	}
      
      list->live_version = live_version;
    }
  return true;
}
