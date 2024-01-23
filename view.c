#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "info.h"

Status read_validate(char *argv[],Info *info)
{
	if((strstr(argv[2],".mp3"))!=NULL)                                                    //check the input file is mp3 or not
	{
		printf("MP3 Tag Reader & Editor :\n---------------------------------------\n");
	}
	else
	{
		printf("Not a mp3 file\n");
		return e_failure;

	}
	info->fp=fopen(argv[2],"r");
	if(info->fp==NULL)
	{
		printf("File does not exist\n");
		return e_failure;
	}
	else
	{
		char arr[3];
		fread(arr,sizeof(char),3,info->fp);
		arr[3]='\0';
		if(!(strcmp(arr,"ID3")))                                                      //check the MP3 version 
		{
			printf("Mp3 Version matched \n");

		}
		else
		{
			printf("Mp3 Version not matched \n");
			return e_failure;
		}
		fread(arr,1,2,info->fp);
		arr[2]='\0';
		if(arr[0]==3 && arr[1]==0)                                                  //check the sub version id
		{
			printf("Version ID  : 2.3\n");
		}
		else
		{
			printf("Mp3 Sub version not matched\n");
			return e_failure;
		}
		fseek(info->fp,1,SEEK_CUR);
		long int a;
		fread(&a,4,1,info->fp);
		info->file_size=a;
		return e_success;

	}

}
/* Collet the Song details
 * Store in a structure
 */
Status view(Info *info)
{
	char arr[4];
	unsigned char s;
	int j=0;
	int c=0;
	do{
	fread(arr,1,4,info->fp);
	if(!(strcmp(arr,"TIT2")))                                                           
	{
		fseek(info->fp,3,SEEK_CUR);
		fread(&s,1,1,info->fp);
		info->size_song_name=s;
		info->song_name_TIT2=malloc(info->size_song_name);
		string(info->size_song_name,info->song_name_TIT2,info);
	     printf("Title      : %s\n",info->song_name_TIT2);
		 c++;
		
    }
    else if(!(strcmp(arr,"TPE1")))
	{
		fseek(info->fp,3,SEEK_CUR);
		fread(&s,1,1,info->fp);
		info->size_artist=s;
		info->artist_TPE1=malloc(info->size_artist);
		string(info->size_artist,info->artist_TPE1,info);
	    printf("Artist     : %s\n",info->artist_TPE1);
		c++;
		
	}
	else if(!(strcmp(arr,"TALB")))
	{
		fseek(info->fp,3,SEEK_CUR);
		fread(&s,1,1,info->fp);
		info->size_album=s;
		info->album_TALB=malloc(info->size_album);
		string(info->size_album,info->album_TALB,info);
	    printf("Album      : %s\n",info->album_TALB);
		c++;
	}

	else if(!(strcmp(arr,"TYER")))
	{
		fseek(info->fp,3,SEEK_CUR);
		fread(&s,1,1,info->fp);
		info->size_year=s;
		info->year=malloc(info->size_year);
		string(info->size_year,info->year,info);
	    printf("Year       : %s\n",info->year);
		c++;
	}

	else if(!(strcmp(arr,"TCOM")))
	{
		fseek(info->fp,3,SEEK_CUR);
		fread(&s,1,1,info->fp);
		info->size_composer=s;
		info->composer_TCOM=malloc(info->size_composer);
		string(info->size_composer,info->composer_TCOM,info);
	    printf("Composer   : %s\n",info->composer_TCOM);
		c++;
    }

	else if(!(strcmp(arr,"TCON")))
	{
		fseek(info->fp,3,SEEK_CUR);
		fread(&s,1,1,info->fp);
		info->size_genre=s;
		info->genre_TCON=malloc(info->size_genre);
		string(info->size_genre,info->genre_TCON,info);
	    printf("Genre      : %s\n",info->genre_TCON);
		c++;
	
	
	}

   else if(!(strcmp(arr,"COMM")))
	{
		fseek(info->fp,2,SEEK_CUR);
		unsigned char x;
		fread(&x,1,1,info->fp);
		fread(&s,1,1,info->fp);
		info->size_comment=x+s;
		//printf("%ld\n",info->size_comment);
		info->comment_COMM=malloc(info->size_comment);
		string(info->size_comment,info->comment_COMM,info);
	    printf("Comment    : %s\n",info->comment_COMM);
		c++;
		
	
	}
	else if(((strcmp(arr,"TIT2"))||(strcmp(arr,"TPE1"))||(strcmp(arr,"TALB"))||(strcmp(arr,"TCOM"))||(strcmp(arr,"TCON"))||(strcmp(arr,"TYER"))||(strcmp(arr,"COMM")))==1)
		
	{
		fseek(info->fp,3,SEEK_CUR);
		fread(&s,1,1,info->fp);
		long int size=s;
		fseek(info->fp,5,SEEK_CUR);
		fseek(info->fp,(size-3),SEEK_CUR);
		char ch;

	}
	if(c==7)
	{
		break;
	}
	}while(!feof(info->fp));
	fclose(info->fp);
	return e_success;

}
/* store only printable characters*/
char string(long int size,char *fptr,Info *info)
{
       char s;
	   int j=0;
		fseek(info->fp,2,SEEK_CUR);
		char str[size];
		for(int i=0;i<(size);i++)
		{
	     	fread(&s,1,1,info->fp);
			if((s>=0x41&& s<=0x5A)||(s>=0x61 && s<=0x7A)|| s==0x2E|| (s>=0x30 && s<=0x39))
			{
				str[j]=s;
				j++;

			}
    	}  
            str[j]='\0';
			strcpy(fptr,str);

     
}
