#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"

map_Node* addNode(char input_key[], char input_value[], int version)
{
  map_Node* newnode = (map_Node*) malloc(sizeof(map_Node));
  // newnode->key = malloc(sizeof(STR_SIZE));
  // newnode->value = malloc(sizeof(STR_SIZE));
  strcpy(newnode->key, input_key);
  strcpy(newnode->value, input_value);
  newnode->next = NULL;
  newnode->prev = NULL;
  newnode->node_version = version;
  
  newnode->mod = (map_Mod*) malloc(sizeof(map_Mod));
  //  newnode->mod->key = malloc(sizeof(STR_SIZE));
  //  newnode->mod->value = malloc(sizeof(STR_SIZE));
  strcpy(newnode->mod->key, JUNK);
  strcpy(newnode->mod->value, JUNK);
  newnode->mod->version = UNUSED;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
  
  return newnode;
}



map_fp* map_init_fp()
{
  map_fp* newlist = (map_fp*) malloc(sizeof(map_fp));

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




void map_search_fp(map_fp* list, char str[])
{
    
  char search_key[STR_SIZE];
  int version;

  sscanf(str, "%[^,],%d", search_key, &version);
    
  if(list->live_version < version)
    {
      printf("Entered version does not exist\n");
      return;
    }

  map_Node* lCrawl = (map_Node*) malloc(sizeof(map_Node));

  if(!lCrawl)	
    {
      printf("Memory allocation error");
      return;
    }

  printf("Searching list of version %d\n", version);
	
  for(lCrawl = list->head[version]; lCrawl != NULL; )
    {
      if((lCrawl->mod->version <= version) && (lCrawl->mod->version != UNUSED))
	{
	  if(!strcmp(lCrawl->mod->key, search_key))
	    {
	      printf("Key found\nKey : %s, Value : %s\n", lCrawl->mod->key, lCrawl->mod->value);
	      return;
	    }
	  lCrawl = lCrawl->mod->next;
	}
      else
	{
	  if(!strcmp(lCrawl->key, search_key))
	    {
	      printf("Key found\nKey : %s, Value : %s\n", lCrawl->key, lCrawl->value);
	      return;
	    }

	  lCrawl = lCrawl->next;
	}
    }
  
  printf("Key not found\n");
}




void map_print_fp(map_fp* list, int version)
{
  if(list->live_version < version)
    {
      printf("Entered version does not exist\n");
      return;
    }
  
  map_Node* pCrawl = (map_Node*) malloc(sizeof(map_Node));
  
  printf("List of version %d\n", version);
	
  if(!pCrawl)	
    {
      printf("Memory allocation error\n");
      return;
    }

  for(pCrawl = list->head[version]; pCrawl != NULL;)
    {
      if(pCrawl->node_version > version)
      	break;
      
      if((pCrawl->mod->version <= version) && (pCrawl->mod->version > UNUSED))
	{
	  printf("Key : %s, Value : %s\n", pCrawl->mod->key, pCrawl->mod->value);
	  pCrawl = pCrawl->mod->next;
	}
      else
	{
	  printf("Key : %s, Value : %s\n", pCrawl->key, pCrawl->value);
	  pCrawl = pCrawl->next;
	}
    }
  
  printf("NULL\n");
}


map_Node* map_update_parentLeft_list_fp(map_fp* list, map_Node* lCrawl, map_Node* newnode, int live_version, int version)
{

  if(lCrawl == NULL) return NULL;

  if(lCrawl->mod->version == UNUSED)
    {
      strcpy(lCrawl->mod->key, lCrawl->key);
      strcpy(lCrawl->mod->value,  lCrawl->value);
      
      lCrawl->mod->version = live_version;
      lCrawl->mod->next = newnode;
      //lCrawl->mod->prev = lCrawl->prev;
      lCrawl->mod->prev = map_update_parentLeft_list_fp(list, lCrawl->prev, lCrawl, live_version, version);
 
      list->head[live_version] = list->head[version];
      return lCrawl;
    }
  else
    {
      map_Node* newnode_parent;
      /* map_Node* newnode_parent = addNode(lCrawl->mod->key, lCrawl->mod->value, live_version);
    
	 newnode_parent->next = newnode;

	 if(lCrawl->mod->prev == NULL)
	 {
	 list->head[live_version] = newnode_parent;
	 return newnode_parent;
	 }

	 newnode_parent->prev = map_update_parentLeft_list_fp(list, lCrawl->mod->prev, newnode_parent, live_version, version);
      */

                      
      if(lCrawl->mod->version <= version)
	{
	  newnode_parent = addNode(lCrawl->mod->key, lCrawl->mod->value, live_version);
	  newnode_parent->next = newnode;

	  if(lCrawl->mod->prev == NULL)
	    {
	      list->head[live_version] = newnode_parent;
	      return newnode_parent;
	    }

	  newnode_parent->prev = map_update_parentLeft_list_fp(list, lCrawl->mod->prev, newnode_parent, live_version, version);
	}
      else
	{
	  newnode_parent = addNode(lCrawl->key, lCrawl->value, live_version);
	  newnode_parent->next = newnode;

	  if(lCrawl->prev == NULL)
	    {
	      list->head[live_version] = newnode_parent;
	      return newnode_parent;
	    }

	  newnode_parent->prev = map_update_parentLeft_list_fp(list, lCrawl->prev, newnode_parent, live_version, version);
	}
      return newnode_parent;
    }

}



map_Node* map_update_parentRight_list_fp(map_fp* list, map_Node* lCrawl, map_Node* newnode, int live_version, int version)
{
  if(lCrawl == NULL) return NULL;

  if(lCrawl->node_version > version) return NULL;
  
  if(lCrawl->mod->version == UNUSED)
    {
      strcpy(lCrawl->mod->key, lCrawl->key);
      strcpy(lCrawl->mod->value, lCrawl->value);
            
      lCrawl->mod->version = live_version;
      lCrawl->mod->prev = newnode;
      //lCrawl->mod->next = lCrawl->next;
      newnode->next = lCrawl;
      lCrawl->mod->next =  map_update_parentRight_list_fp(list, lCrawl->next, lCrawl, live_version, version);
      
      return lCrawl;
    }
  else
    {
      map_Node* newnode_parent;
      /* map_Node* newnode_parent = addNode(lCrawl->mod->key, lCrawl->mod->value, live_version);

	 newnode_parent->next = map_update_parentRight_list_fp(list, lCrawl->mod->next, newnode_parent, live_version, version);

	 newnode_parent->prev = newnode;
      */

      if(lCrawl->mod->version <= version)
	{	  
	  newnode_parent = addNode(lCrawl->mod->key, lCrawl->mod->value, live_version);
	  newnode_parent->prev = newnode;
	  newnode_parent->next = map_update_parentRight_list_fp(list, lCrawl->mod->next, newnode_parent, live_version, version);
	}
      else
	{
	  newnode_parent = addNode(lCrawl->mod->key, lCrawl->mod->value, live_version);

	  newnode_parent->prev = newnode;
	  newnode_parent->next = map_update_parentRight_list_fp(list, lCrawl->next, newnode_parent, live_version, version);
	}
      
      return newnode_parent;
    }

}



bool map_insert_fp(map_fp* list, char str[], int index, int version)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }

  int index_count = 0;
  int live_version = list->live_version;

  if(version > live_version)
    {
      printf("Version does not exist\n");
      return false;
    }

  char key[STR_SIZE], value[STR_SIZE];

  sscanf(str, "%[^,],%[^,]", key,value);
  
  map_Node* newnode = addNode(key, value, UNUSED);
      
  map_Node* lCrawl = (map_Node*) malloc(sizeof(map_Node));
  map_Node* lCrawl_prev = (map_Node*) malloc(sizeof(map_Node));
  
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
 
  for(lCrawl = list->head[version], lCrawl_prev = list->head[version]; lCrawl != NULL; index_count++)
    {
      if(lCrawl != list->head[version])
	lCrawl_prev = lCrawl->prev;
      
      if(index_count == index) break;
      
      if((lCrawl->mod->version <= version) && lCrawl->mod->version != UNUSED)
	lCrawl = lCrawl->mod->next;
      else
	lCrawl = lCrawl->next;
    }

  if(list->head[live_version] == NULL)
    {
      list->head[live_version] = newnode;
      newnode->node_version = live_version;
      return true;
    }

  if(lCrawl == NULL) index_count--;
  
  if(index != index_count) 
    {
      printf("Index greater than length of the list. The element will be appended at the end of the list\n");
    }
  
  if(lCrawl_prev == list->head[version] && index == 1)
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
      
      //lCrawl->mod->data = lCrawl->data;
      //lCrawl->mod->version = live_version;

      newnode->node_version = live_version;
      
      if(index != 0)
	{
	  lCrawl->mod->next = newnode;
	  lCrawl->mod->prev = lCrawl->prev;

	  newnode->next = map_update_parentRight_list_fp(list, lCrawl->next, newnode, live_version, version);
	  newnode->prev = map_update_parentLeft_list_fp(list, lCrawl, newnode, live_version, version);
	}
      else
	{
	  newnode->next = lCrawl;
	  
	  strcpy(lCrawl->mod->key, lCrawl->key);
	  strcpy(lCrawl->mod->value, lCrawl->value);
      
  	  lCrawl->mod->next = lCrawl->next;
	  lCrawl->mod->prev = newnode;
	  lCrawl->mod->version = live_version;
	  
	  list->head[live_version] = newnode;
      	}
    }
  else
    {
      live_version++;
      
      newnode->node_version = live_version;

      if(index !=0)
	{
	  /* newnode->next = map_update_parentRight_list_fp(list, lCrawl->mod->next, newnode, live_version, version);
	     newnode->prev = map_update_parentLeft_list_fp(list, lCrawl, newnode, live_version, version);*/
	  if(lCrawl->mod->version <= version)
	    {
	      //printf("1\n");
	      newnode->next = map_update_parentRight_list_fp(list, lCrawl->mod->next, newnode, live_version, version);
	      newnode->prev = map_update_parentLeft_list_fp(list, lCrawl, newnode, live_version, version);

	      //if(newnode->prev != NULL) printf("newnode prev %d vers %dn nernode vers %d\n", newnode->prev->data, newnode->prev->node_version, newnode->node_version);
	    }
	  else
	    {
	      newnode->next = map_update_parentRight_list_fp(list, lCrawl->next, newnode, live_version, version);
	      newnode->prev = map_update_parentLeft_list_fp(list, lCrawl, newnode, live_version, version);
	    }
	}
      else
	{
	  map_Node* trailNode;
	  /*	  map_Node* trailNode = addNode(lCrawl->mod->key, lCrawl->mod->value, live_version);
	 
		  trailNode->prev = newnode;
		  trailNode->next = map_update_parentRight_list_fp(list, lCrawl->mod->next, trailNode, live_version, version);	
	  
		  newnode->next = trailNode;
  	  
		  list->head[live_version] = newnode;
	  */
	  
	  if(lCrawl->mod->version <= version)
	    {
	      //printf("2\n");
	      trailNode = addNode(lCrawl->mod->key, lCrawl->mod->value, live_version);
	      trailNode->next = map_update_parentRight_list_fp(list, lCrawl->mod->next, trailNode, live_version, version);	
	    }
	  else
	    {
	      trailNode = addNode(lCrawl->key, lCrawl->value, live_version);
	      trailNode->next = map_update_parentRight_list_fp(list, lCrawl->next, trailNode, live_version, version);	
	    }

	  trailNode->prev = newnode;
	  newnode->next = trailNode;
  	  
	  list->head[live_version] = newnode;
	}
    }
  
  list->live_version = live_version;
  return true;
}



bool map_update_fp(map_fp* list, char str[], int index, int version)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
  
  int index_count = 0;
  int live_version = list->live_version;

  map_Node* lCrawl = (map_Node*) malloc(sizeof(map_Node));

  if(version > live_version)
    {
      printf("Version does not exist\n");
      return false;
    }
    
  if(!lCrawl)	
    {
      printf("Memory allocation error");
      return false;
    }
 
  for(lCrawl = list->head[version]; lCrawl != NULL; index_count++)
    {
      if(index_count == index) break;
      
      if((lCrawl->mod->version <= version) && lCrawl->mod->version != UNUSED)
	lCrawl = lCrawl->mod->next;
      else
	lCrawl = lCrawl->next;
    }

  if(lCrawl == NULL) index_count--;
  
  if(index != index_count) 
    {
      printf("Index not found in the list. ");
      map_insert_fp(list, str, index, version);
      return true;
    }
  else
    {     
      if(lCrawl->mod->version == UNUSED)
	{  
	  live_version++;

	  char key[STR_SIZE], value[STR_SIZE];
	  sscanf(str, "%[^,],%[^,]", key,value);
	      
	  strcpy(lCrawl->mod->key, key);
	  strcpy(lCrawl->mod->value, value);

	  lCrawl->mod->version = live_version;
	  lCrawl->mod->next = lCrawl->next;
	  lCrawl->mod->prev = lCrawl->prev;

	  list->head[live_version] = list->head[version];
	}
      else
	{
	  live_version++;


	  if(index != 0)
	    {
	      char key[STR_SIZE], value[STR_SIZE];

	      sscanf(str, "%[^,],%[^,]", key,value);
	      map_Node* newnode = addNode(key, value, live_version);

	      if(lCrawl->mod->version <= version)
		{
		  newnode->next = map_update_parentRight_list_fp(list, lCrawl->mod->next, newnode, live_version, version);
		  newnode->prev = map_update_parentLeft_list_fp(list, lCrawl->mod->prev, newnode, live_version, version);
		}
	      else
		{
		  newnode->next = map_update_parentRight_list_fp(list, lCrawl->next, newnode, live_version, version);
		  newnode->prev = map_update_parentLeft_list_fp(list, lCrawl->prev, newnode, live_version, version);
		}
	    }
	  else
	    {
	      char key[STR_SIZE], value[STR_SIZE];

	      sscanf(str, "%[^,],%[^,]", key,value);
	      map_Node* newnode = addNode(key, value, live_version);

	      if(lCrawl->mod->version <= version)
		newnode->next = map_update_parentRight_list_fp(list, lCrawl->mod->next, newnode, live_version, version);
	      else
		newnode->next = map_update_parentRight_list_fp(list, lCrawl->next, newnode, live_version, version);
		
	      list->head[live_version] = newnode;
	    }

	  /* 
	     if(index != 0)
	     {
	     map_Node* newnode = addNode(data, live_version);

	     if(lCrawl->node_version <= version)
	     {
	     newnode->next = map_update_parentRight_list_fp(list, lCrawl->next, newnode, live_version, version);
	     newnode->prev = map_update_parentLeft_list_fp(list, lCrawl->prev, newnode, live_version, version);
	     }
	     else
	     {
	     newnode->next = map_update_parentRight_list_fp(list, lCrawl->mod->next, newnode, live_version, version);
	     newnode->prev = map_update_parentLeft_list_fp(list, lCrawl->mod->prev, newnode, live_version, version);
	     }
	     }
	     else
	     {
	     map_Node* newnode = addNode(data, live_version);

	     if(lCrawl->node_version <= version)
	     newnode->next = map_update_parentRight_list_fp(list, lCrawl->next, newnode, live_version, version);
	     else
	     newnode->next = map_update_parentRight_list_fp(list, lCrawl->mod->next, newnode, live_version, version);

	     list->head[live_version] = newnode;
	     }*/
	}

      list->live_version = live_version;
    }
  return true;
}




bool map_delete_fp(map_fp* list, int index, int version)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
      
  int index_count = 0;
  int live_version = list->live_version;

  map_Node* lCrawl = (map_Node*) malloc(sizeof(map_Node));

  if(version > live_version)
    {
      printf("Version does not exist\n");
      return false;
    }
     
  if(!lCrawl)	
    {
      printf("Memory allocation error");
      return false;
    }
  
  if(list->head[version] == NULL)
    {
      printf("List is empty. Cannot delete from empty list");
      return false;
    }
   
  if((list->head[version]->next == NULL) && (list->head[version]->mod->next == NULL) || (version == 0))
    {
      live_version++;
      list->head[live_version] = NULL;

      list->live_version = live_version;
      return true;
    }
  
  for(lCrawl = list->head[version]; lCrawl != NULL; index_count++)
    {
      if(index_count == index) break;
      
      if((lCrawl->mod->version <= version) && lCrawl->mod->version != UNUSED)
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
	  if((lCrawl->mod->version == UNUSED) || (lCrawl->mod->version > version))
	    {
	      if(lCrawl->next->mod->version == UNUSED)
		{  
		  live_version++;
		
		  strcpy(lCrawl->next->mod->key, lCrawl->next->key);
		  strcpy(lCrawl->next->mod->value, lCrawl->next->value);
		  
		  lCrawl->next->mod->version = live_version;

		  lCrawl->next->mod->next = lCrawl->next->next;
		  lCrawl->next->mod->prev = lCrawl->prev;

		  list->head[live_version] = lCrawl->next;
		}
	      else
		{
		  live_version++;
		  /////////// if check
		  map_Node* newnode;
		  
		  if(lCrawl->next->mod->version <= version)
		    {
		      newnode = addNode(lCrawl->next->mod->key, lCrawl->next->mod->value, live_version);
		      newnode->next = map_update_parentRight_list_fp(list, lCrawl->next->mod->next, newnode, live_version, version);
		    }
		  else
		    {
		      newnode = addNode(lCrawl->next->key, lCrawl->next->value, live_version);
		      newnode->next = map_update_parentRight_list_fp(list, lCrawl->next->next, newnode, live_version, version);
		    }
		  
		  list->head[live_version] = newnode;
		}
	    }
	  else
	    {
	      if(lCrawl->mod->next->mod->version == UNUSED) 
		{  
		  live_version++;

		  strcpy(lCrawl->mod->next->mod->key, lCrawl->mod->next->key);
		  strcpy(lCrawl->mod->next->mod->value, lCrawl->mod->next->value);
		  
		  
		  lCrawl->mod->next->mod->version = live_version;
		  lCrawl->mod->next->mod->next = lCrawl->mod->next->next;
		  lCrawl->mod->next->mod->prev = lCrawl->mod->prev;

		  list->head[live_version] = lCrawl->mod->next;
		}
	      else
		{
		  live_version++;

		  map_Node* newnode;;

		  if(lCrawl->mod->next->mod->version <= version)
		    {
		      newnode = addNode(lCrawl->mod->next->mod->key, lCrawl->mod->next->mod->value, live_version);
		      newnode->next = map_update_parentRight_list_fp(list, lCrawl->mod->next->mod->next, newnode, live_version, version);
		    }
		  else
		    {
		      newnode = addNode(lCrawl->mod->next->key, lCrawl->mod->next->value, live_version);
		      newnode->next = map_update_parentRight_list_fp(list, lCrawl->mod->next->next, newnode, live_version, version);
		    }
		  
		  list->head[live_version] = newnode;
		}
	    }
	  
	  list->live_version = live_version;
	  return true;
	}
      
      if((lCrawl->next == NULL) && (lCrawl->mod->version == UNUSED) || (lCrawl->mod->version > version))
	{
	  if(lCrawl->prev->mod->version == UNUSED)
	    {  
	      live_version++;

	      strcpy(lCrawl->prev->mod->key, lCrawl->prev->key);
	      strcpy(lCrawl->prev->mod->value, lCrawl->prev->value);

	      lCrawl->prev->mod->version = live_version;
	      lCrawl->prev->mod->next = lCrawl->next;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      list->head[live_version] = list->head[version];
	    }
	  else
	    {
	      live_version++;

	      map_Node* newnode;
	      
	      if(lCrawl->prev->mod->version <= version)
		{
		  newnode = addNode(lCrawl->prev->mod->key, lCrawl->prev->mod->value, live_version);
		  newnode->prev = map_update_parentLeft_list_fp(list, lCrawl->prev->mod->prev, newnode, live_version, version);

		  if(lCrawl->prev->mod->prev == NULL) list->head[live_version] = newnode;
		}
	      else
		{
		  newnode = addNode(lCrawl->prev->key, lCrawl->prev->value, live_version);
		  newnode->prev = map_update_parentLeft_list_fp(list, lCrawl->prev->prev, newnode, live_version, version);

		  if(lCrawl->prev->prev == NULL) list->head[live_version] = newnode;
		}
	    }
 
	  list->live_version = live_version;
	  return true;
	}
      
      if((lCrawl->mod->next == NULL) && (lCrawl->mod->version != UNUSED) && (lCrawl->mod->version <= version))
	{
	  if(lCrawl->mod->prev->mod->version == UNUSED)
	    {  
	      live_version++;

	      strcpy(lCrawl->mod->prev->mod->key, lCrawl->mod->prev->key);
	      strcpy(lCrawl->mod->prev->mod->value, lCrawl->mod->prev->value);

	      lCrawl->mod->prev->mod->version = live_version;
	      lCrawl->mod->prev->mod->next = lCrawl->mod->next;
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;

	      list->head[live_version] = list->head[version];
	    }
	  else
	    {
	      live_version++;

	      map_Node* newnode;;

	      if(lCrawl->mod->prev->mod->version <= version)
		{
		  newnode = addNode(lCrawl->mod->prev->mod->key, lCrawl->mod->prev->mod->value, live_version);
		  newnode->prev = map_update_parentLeft_list_fp(list, lCrawl->mod->prev->mod->prev, newnode, live_version, version);

		  if(lCrawl->mod->prev->mod->prev == NULL) list->head[live_version] = newnode;
		}
	      else
		{
		  newnode = addNode(lCrawl->mod->prev->key, lCrawl->mod->prev->value, live_version);
		  newnode->prev = map_update_parentLeft_list_fp(list, lCrawl->mod->prev->prev, newnode, live_version, version);

		  if(lCrawl->mod->prev->prev == NULL) list->head[live_version] = newnode;
		}
	    }

	  list->live_version = live_version;
	  return true;
	}
         

      if((lCrawl->mod->version == UNUSED) || (lCrawl->mod->version > version))
	{
	  if((lCrawl->prev->mod->version == UNUSED) && (lCrawl->next->mod->version == UNUSED))
	    {  
	      live_version++;
	      //printf("1\n");

	      strcpy(lCrawl->prev->mod->key, lCrawl->prev->key);
	      strcpy(lCrawl->prev->mod->value, lCrawl->prev->value);
	      
	      lCrawl->prev->mod->version = live_version;
	      lCrawl->prev->mod->next = lCrawl->next;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      strcpy(lCrawl->next->mod->key, lCrawl->next->key);
	      strcpy(lCrawl->next->mod->value, lCrawl->next->value);
	      
	      lCrawl->next->mod->version = live_version;
	      lCrawl->next->mod->next = lCrawl->next->next;
	      lCrawl->next->mod->prev = lCrawl->prev;

	      list->head[live_version] = list->head[version];
	    }
	  else if((lCrawl->prev->mod->version == UNUSED) && (lCrawl->next->mod->version != UNUSED))
	    {
	      live_version++;
	      //printf("2\n");
	      map_Node* newnode;
	      
	      strcpy(lCrawl->prev->mod->key, lCrawl->prev->key);
	      strcpy(lCrawl->prev->mod->value, lCrawl->prev->value);
	      
	      lCrawl->prev->mod->version = live_version;
	      lCrawl->prev->mod->next = newnode;
	      lCrawl->prev->mod->prev = lCrawl->prev->prev;

	      if(lCrawl->next->mod->version <= version)
		{
		  newnode = addNode(lCrawl->next->mod->key, lCrawl->next->mod->value, live_version);
		  newnode->next = map_update_parentRight_list_fp(list, lCrawl->next->mod->next, newnode, live_version, version);
		}
	      else
		{
		  newnode = addNode(lCrawl->next->key, lCrawl->next->value, live_version);
		  newnode->next = map_update_parentRight_list_fp(list, lCrawl->next->next, newnode, live_version, version);
		}
	      
	      newnode->prev = lCrawl->prev;

	      list->head[live_version] = list->head[version];
	    }
	  else if((lCrawl->prev->mod->version != UNUSED) && (lCrawl->next->mod->version == UNUSED))
	    {
	      live_version++;
	      //printf("3\n");
	      map_Node* newnode;
	      
	      strcpy(lCrawl->next->mod->key, lCrawl->next->key);
	      strcpy(lCrawl->next->mod->value, lCrawl->next->value);
	      
	      lCrawl->next->mod->version = live_version;
	      lCrawl->next->mod->next = lCrawl->next->next;
	      lCrawl->next->mod->prev = newnode;

	      if(lCrawl->prev->mod->version <= version)
		{
		  newnode = addNode(lCrawl->prev->mod->key, lCrawl->prev->mod->value, live_version);
		  newnode->prev = map_update_parentLeft_list_fp(list, lCrawl->prev->mod->prev, newnode, live_version, version);

		  if(lCrawl->prev->mod->prev == NULL)  list->head[live_version] = newnode;
		}
	      else
		{
		  newnode = addNode(lCrawl->prev->key, lCrawl->prev->value, live_version);
		  newnode->prev = map_update_parentLeft_list_fp(list, lCrawl->prev->prev, newnode, live_version, version);

		  if(lCrawl->prev->prev == NULL)  list->head[live_version] = newnode;
		}

	      newnode->next = lCrawl->next;
	    }
	  else
	    {
	      live_version++;
	      //printf("4\n");       
	      map_Node* newnode_prev;
	      map_Node* newnode_next;

	      if(lCrawl->prev->mod->version <= version)
		{
		  newnode_prev = addNode(lCrawl->prev->mod->key, lCrawl->prev->mod->value, live_version);
		  newnode_prev->prev = map_update_parentLeft_list_fp(list, lCrawl->prev->mod->prev, newnode_prev, live_version, version);

		  if(lCrawl->prev->mod->prev == NULL)  list->head[live_version] = newnode_prev;
		}
	      else
		{
		  newnode_prev = addNode(lCrawl->prev->key, lCrawl->prev->value, live_version);
		  newnode_prev->prev = map_update_parentLeft_list_fp(list, lCrawl->prev->prev, newnode_prev, live_version, version);

		  if(lCrawl->prev->prev == NULL)  list->head[live_version] = newnode_prev;
		}
	      
	      if(lCrawl->next->mod->version <= version)
		{
		  newnode_next = addNode(lCrawl->next->mod->key, lCrawl->next->mod->value,live_version);
		  newnode_next->next = map_update_parentRight_list_fp(list, lCrawl->next->mod->next, newnode_next, live_version, version);
		}
	      else
		{
		  newnode_next = addNode(lCrawl->next->key, lCrawl->next->value, live_version);
		  newnode_next->next = map_update_parentRight_list_fp(list, lCrawl->next->next, newnode_next, live_version, version);
		}

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	    }
	}
      else
	{
	  if((lCrawl->mod->prev->mod->version == UNUSED) && (lCrawl->mod->next->mod->version == UNUSED))
	    {  
	      live_version++;
	      //printf("5\n");  
	      strcpy(lCrawl->mod->prev->mod->key, lCrawl->mod->prev->key);
	      strcpy(lCrawl->mod->prev->mod->value, lCrawl->mod->prev->value);
	      
	      lCrawl->mod->prev->mod->version = live_version;

	      lCrawl->mod->prev->mod->next = lCrawl->mod->next;
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;

	      strcpy(lCrawl->mod->next->mod->key, lCrawl->mod->next->key);
	      strcpy(lCrawl->mod->next->mod->value, lCrawl->mod->next->value);

	      lCrawl->mod->next->mod->version = live_version;
	      lCrawl->mod->next->mod->next = lCrawl->mod->next->next;
	      lCrawl->mod->next->mod->prev = lCrawl->mod->prev;

	      list->head[live_version] = list->head[version];
	    }
	  else if((lCrawl->mod->prev->mod->version == UNUSED) && (lCrawl->mod->next->mod->version != UNUSED))
	    {
	      live_version++;
	      //printf("6\n"); 	      	  
	      map_Node* newnode;

	      strcpy(lCrawl->mod->prev->mod->key, lCrawl->mod->prev->key);
	      strcpy(lCrawl->mod->prev->mod->value, lCrawl->mod->prev->value);

	      lCrawl->mod->prev->mod->version = live_version;
	      
	      lCrawl->mod->prev->mod->prev = lCrawl->mod->prev->prev;
	      lCrawl->mod->prev->mod->next = newnode; 
	     
	      
	      if(lCrawl->mod->next->mod->version <= version)
		{
		  newnode = addNode(lCrawl->mod->next->mod->key, lCrawl->mod->next->mod->value, live_version);
		  newnode->next = map_update_parentRight_list_fp(list, lCrawl->mod->next->mod->next, newnode, live_version, version);
		}
	      else
		{
		  newnode = addNode(lCrawl->mod->next->key, lCrawl->mod->next->value, live_version);
		  newnode->next = map_update_parentRight_list_fp(list, lCrawl->mod->next->next, newnode, live_version, version);
		}

	      newnode->prev = lCrawl->mod->prev;
	      
	      list->head[live_version] = list->head[version];
	    }
	  else if((lCrawl->mod->prev->mod->version != UNUSED) && (lCrawl->mod->next->mod->version == UNUSED))
	    {
	      live_version++;
	      //printf("7\n");	      	      
	      map_Node* newnode;       

	      strcpy(lCrawl->mod->next->mod->key, lCrawl->mod->next->key);
	      strcpy(lCrawl->mod->next->mod->value, lCrawl->mod->next->value);
	     
	      lCrawl->mod->next->mod->version = live_version;
	      lCrawl->mod->next->mod->next = lCrawl->mod->next->next;
	      lCrawl->mod->next->mod->prev = newnode;

	      if(lCrawl->mod->prev->mod->version <= version)
		{
		  newnode = addNode(lCrawl->mod->prev->mod->key, lCrawl->mod->prev->mod->value, live_version);
		  newnode->prev = map_update_parentLeft_list_fp(list, lCrawl->mod->prev->mod->prev, newnode, live_version, version);

		  if(lCrawl->mod->prev->mod->prev == NULL)  list->head[live_version] = newnode;
		}
	      else
		{
		  newnode = addNode(lCrawl->mod->prev->key, lCrawl->mod->prev->value, live_version);
		  newnode->prev = map_update_parentLeft_list_fp(list, lCrawl->mod->prev->prev, newnode, live_version, version);

		  if(lCrawl->mod->prev->prev == NULL)  list->head[live_version] = newnode;
		}

	      newnode->next = lCrawl->mod->next;
	    }
	  else
	    {
	      live_version++;
	      //printf("8\n");	        
	      map_Node* newnode_prev;
	      map_Node* newnode_next;

	      if(lCrawl->mod->prev->mod->version <= version)
		{
		  newnode_prev = addNode(lCrawl->mod->prev->mod->key, lCrawl->mod->prev->mod->value,live_version);
		  newnode_prev->prev = map_update_parentLeft_list_fp(list, lCrawl->mod->prev->mod->prev, newnode_prev, live_version, version);

		  if(lCrawl->mod->prev->mod->prev == NULL)  list->head[live_version] = newnode_prev;
		}
	      else
		{
		  newnode_prev = addNode(lCrawl->mod->prev->key, lCrawl->mod->prev->value, live_version);
		  newnode_prev->prev = map_update_parentLeft_list_fp(list, lCrawl->mod->prev->prev, newnode_prev, live_version, version);

		  if(lCrawl->mod->prev->prev == NULL)  list->head[live_version] = newnode_prev;
		}
	      
	      if(lCrawl->mod->next->mod->version <= version)
		{
		  newnode_next = addNode(lCrawl->mod->next->mod->key, lCrawl->mod->next->mod->value, live_version);
		  newnode_next->next = map_update_parentRight_list_fp(list, lCrawl->mod->next->mod->next, newnode_next, live_version, version);
		}
	      else
		{
		  newnode_next = addNode(lCrawl->mod->next->key, lCrawl->mod->next->value, live_version);
		  newnode_next->next = map_update_parentRight_list_fp(list, lCrawl->mod->next->next, newnode_next, live_version, version);
		}

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;
	    }
	  	  
	}
      
      list->live_version = live_version;
    }
  return true;
}

