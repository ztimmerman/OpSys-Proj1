//File for file resolution
//will integrate into proj1.c
//Zachary Timmerman for COP4610

/***********************INLUDED APIS****************/
#include <stdio.h>	//io
#include <string.h>	//c-strings
#include <stdlib.h>	//memcpy,memmove
#include <dirent.h> //for directory entry search

/*
 * First pathRes: designed to deal with commands
 * VARIABLE RETURNED MUST BE FREED IF NOT ERRORCODE
 */

int fileExists(const char * directory, const char * ourFile) {
 DIR *dir;
 struct dirent *ent;
 int counter = 0;
 if ((dir = opendir (directory)) != NULL) {
   /* print all the files and directories within directory */
   while ((ent = readdir (dir)) != NULL) {
//      printf ("%s\n", ent->d_name);
    if (strcmp(ent->d_name,ourFile) == 0)	{
      closedir (dir);
      return counter;
    }  else  {
      counter++;
    }
   }
   closedir (dir);
   return -2;
 } else {
   /* could not open directory */
//    perror ("");
   return -1;
 }
}

char * pathRes(char * newPath, const char * m_PATH){
    char * true_path = 0;

    int path_size = 0;
    int colons_num = 0;
    for (int i = 0; m_PATH[i] != '\0'; i++) { //get size of array and number of colons
      path_size++;
      if (m_PATH[i] == ':') {
        colons_num++;   //colons_num + 1 will equal number of paths to search
      }
    }
    //printf("%d\n",path_size);
    //printf("%d\n",colons_num);
    char ** path_arr; //path_arr will hold all possible paths
    path_arr = calloc(colons_num+1,sizeof(char*));
    char* temp_str; //will hold string data until copied into path_arr
    const char* itr = m_PATH;      //pointer to different parts of m_PATH
    const char* delim;            //pointer to delimiter of ':'
    //printf("%s\n",itr);
    int foundDir = -3;
    for (int i = 0; i <= colons_num; i++) {
      temp_str = calloc(255,sizeof(char));
      delim = strchr(itr,':');
      if (delim != 0) {
        strncpy(temp_str,itr,delim - itr);
        path_arr[i] = temp_str;
        itr = delim + 1;
      } else  {
        strcpy(temp_str,itr);
        //printf("temp_str: %s\n",temp_str);
        path_arr[i] = temp_str;
      }
    }

    for (int i = 0; i <= colons_num; i++)  {
      //printf("%s\n",path_arr[i]);
      foundDir = fileExists(path_arr[i],newPath);
      if (foundDir > -1 && true_path == 0)  {
        //printf("%s\n",temp_str);
        true_path = calloc(strlen(path_arr[i]) + strlen(newPath) + 2,1);
        strcpy(true_path,path_arr[i]);
        strcat(true_path,"/");
        strcat(true_path,newPath);
      }
    }

    //free the ram!
    for (int i = 0; i <= colons_num; i++) {
      temp_str = path_arr[i];
      free(temp_str);
    }
    free(path_arr);
    if (true_path != 0) {
      return true_path;
    } else  {
      return 0;
    }
}

char * homeProcess(char * oldPath, const char * homePath)  {
  char * newPath;
  if (oldPath[0] == '~')  {
    newPath = calloc(strlen(oldPath) + strlen(homePath),1);
    strcpy(newPath,homePath);
    strcat(newPath,oldPath+1);
    return newPath;
  } else  {
    return oldPath;
  }
}

char * relativeProcess(char * curr_pwd, char * obj)  {
  char * newObj;
  int isValid = fileExists(curr_pwd,obj);
  if (isValid >= 0) {
    newObj = calloc(strlen(curr_pwd) + strlen(obj) + 2,1);
    strcpy(newObj,curr_pwd);
    strcat(newObj,"/");
    strcat(newObj,obj);
    return newObj;
  } else  {
      return 0;
  }
}

int main()
{
  char * paths = "/home/zacharytimmerman/bin:/home/zacharytimmerman/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/usr/lib/jvm/java-8-oracle/bin:/usr/lib/jvm/java-8-oracle/db/bin:/usr/lib/jvm/java-8-oracle/jre/bin";
  char * pwd = "/home/zacharytimmerman/opsys/OpSys-Proj1";
  char * z_home = "/home/zacharytimmerman";
  char * newPath = ".git";
  char * true_path;

/*
  true_path = pathRes(newPath,paths);
  printf("%s\n",true_path);
  free(true_path);
*/

/*
  true_path = homeProcess(pwd,z_home);
  printf("%s\n",true_path);
  free(true_path);
*/
  true_path = relativeProcess(pwd,newPath);
  if (true_path != 0) {
    printf("%s\n",true_path);
    free(true_path);
  } else  {
    printf("File not found.\n");
  }

  return 0;
}
