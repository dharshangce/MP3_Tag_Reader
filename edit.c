#include <stdio.h>
#include "info.h"
#include <string.h>
#include <stdlib.h>



Status read_validate_edit(char *argv[],Edit *edit_info)
{
	if((strstr(argv[2],".mp3")!=NULL))
	{
		printf("MP3 Tag Reader & Editor :\n----------------------------------------------\n");

	}
	else
	{
		printf("Not a mp3 file\n");
		return e_failure;
	}
	edit_info->fptr=fopen(argv[2],"r+");
	if(edit_info->fptr==NULL)
	{
		printf("File does not exist\n");
		return e_failure;
	}
	else
	{
		char arr[3];
		fread(arr,sizeof(char),3,edit_info->fptr);
		arr[3]='\0';
		if(!(strcmp(arr,"ID3")))
		{
			printf("MP3 Version matched\n");

		}
		else
		{
			printf("Mp3 Version not Matched\n");
			return e_failure;
		}
		fread(arr,1,2,edit_info->fptr);
		arr[2]='\0';
		if(arr[0]==3 && arr[1]==0)
		{
			printf("Version ID   :2.3\n");
		}
		else
		{
			printf("MP3 Sub version not matched\n");
			return e_failure;
		}
		fseek(edit_info->fptr,1,SEEK_CUR);
		long  int a;
		fread(&a,4,1,edit_info->fptr);
		edit_info->size_file=a;
		return e_success;
	}
}
/*Fetch the original content from the source file
 * replace the content
 */

Status edit(char *argv[],char *tag,Edit *edit_info)
{

	int j;
	unsigned char c;
	long int s;
	long  int l=strlen(argv[4]);
	char str[4];
	char arg[l];
    char ch;
    while(fread(str,1,4,edit_info->fptr)==4)
	{
		if(!(strcmp(str,"TIT2")))
		{
          if(!(strcmp(tag,str)))
    	  {
			  if(operation(edit_info,argv,&edit_info->TIT2_song_name)==e_success)
			  {
	             break;
				}
		  }
	
		    else
			{
				fseek(edit_info->fptr,3,SEEK_CUR);
				fread(&c,1,1,edit_info->fptr);
				s=c;
				fseek(edit_info->fptr,2,SEEK_CUR);
				fseek(edit_info->fptr,s,SEEK_CUR);
		    }
		}
		else  if(!(strcmp(str,"TPE1")))
	    {
				if(!strcmp(str,tag))
				{
				if(operation(edit_info,argv,&edit_info->TPE1_artist)==e_success)
	            break;
	          }
			  else
				{
				fseek(edit_info->fptr,3,SEEK_CUR);
				fread(&c,1,1,edit_info->fptr);
				s=c;
				fseek(edit_info->fptr,2,SEEK_CUR);
				fseek(edit_info->fptr,s,SEEK_CUR);
			    }
	   }
       else  if(!(strcmp(str,"TALB")))
	    {
				if(!strcmp(str,tag))
				{
					if(operation(edit_info,argv,&edit_info->TALB_album)==e_success)
	                break;
	          }
			  else
				{
				fseek(edit_info->fptr,3,SEEK_CUR);
				fread(&c,1,1,edit_info->fptr);
				s=c;
				fseek(edit_info->fptr,2,SEEK_CUR);
				fseek(edit_info->fptr,s,SEEK_CUR);
			    }
			  
         }

       else  if(!(strcmp(str,"TYER")))
	    {
				if(!strcmp(str,tag))
				{
					if(operation(edit_info,argv,&edit_info->TYER_year)==e_success)
	            break;
	        
	          }
			  else
				{
				fseek(edit_info->fptr,3,SEEK_CUR);
				fread(&c,1,1,edit_info->fptr);
				s=c;
				fseek(edit_info->fptr,2,SEEK_CUR);
				fseek(edit_info->fptr,s,SEEK_CUR);
			    }
			  
		 }

       else  if(!(strcmp(str,"COMM")))
	    {
				if(!strcmp(str,tag))
				{
	            fseek(edit_info->fptr,2,SEEK_CUR);
				unsigned char x;
	            fread(&c,1,1,edit_info->fptr);
	            fread(&x,1,1,edit_info->fptr);
				s=c+x;
	            if(l>s)
	            {
		          printf("Size not enough\n");
		          return e_failure;
	            }
	            char str1[s];
            	fseek(edit_info->fptr,2,SEEK_CUR);
	            int original=ftell(edit_info->fptr);
	            fread(str1,1,s,edit_info->fptr);
	            strcpy(arg,argv[4]);
            	char str2[s];
	            for(int i=0;arg[i]!='\0';i++)
	            {
		              str2[i]=arg[i];
	            }
	            for(int i=l;i<s;i++)
	            {
		              str2[i]='!';
	            }
	            for(int i=0;i<s;i++)
	            {
		              str1[i]=str1[i]&0;

	            } 
	            for(int i=0;i<s;i++)
            	{
		          str1[i]=str1[i]| str2[i];
             	}
	            fseek(edit_info->fptr,original,SEEK_SET);
	            fwrite(str1,1,s,edit_info->fptr);
	            break;
	          }
			  else
				{
				fseek(edit_info->fptr,2,SEEK_CUR);
				fread(&c,1,1,edit_info->fptr);

				unsigned char x;
				fread(&x,1,1,edit_info->fptr);
				s=c+x;
				fseek(edit_info->fptr,2,SEEK_CUR);
				fseek(edit_info->fptr,s,SEEK_CUR);
				
                }
         }

       else  if(!(strcmp(str,"TCOM")))
	    {
				if(!strcmp(str,tag))
				{
					if(operation(edit_info,argv,&edit_info->TCOM_composer)==e_success)
						printf("Composer: %s\n",edit_info->TCOM_composer);
	            break;
	          }
			  else
				{
				fseek(edit_info->fptr,3,SEEK_CUR);
				fread(&c,1,1,edit_info->fptr);
				s=c;
				fseek(edit_info->fptr,2,SEEK_CUR);
				fseek(edit_info->fptr,s,SEEK_CUR);
			    }
	     
		}

       else  if(!(strcmp(str,"TCON")))
	    {
				if(!strcmp(str,tag))
				{
					if(operation(edit_info,argv,&edit_info->TCON_genre)==e_success)
	            break;
	          }
			  else
				{
				fseek(edit_info->fptr,3,SEEK_CUR);
				fread(&c,1,1,edit_info->fptr);
				s=c;
				fseek(edit_info->fptr,2,SEEK_CUR);
				fseek(edit_info->fptr,s,SEEK_CUR);
			    }
		}
			  

	     else if(((strcmp(str,"TIT2"))||(strcmp(str,"TPE1"))||(strcmp(str,"TALB"))||(strcmp(str,"TCOM"))||(strcmp(str,"TCON"))||(strcmp(str,"TYER"))||(strcmp(str,"COMM")))==1)
		 {
          
				fseek(edit_info->fptr,3,SEEK_CUR);
				fread(&c,1,1,edit_info->fptr);
				s=c;
				fseek(edit_info->fptr,2,SEEK_CUR);
				fseek(edit_info->fptr,s,SEEK_CUR);
		 }

		
    }
	fclose(edit_info->fptr);
	return e_success;

    
}
Status operation(Edit *edit_info,char *argv[],char **fpt)
{


	int j;
	unsigned char c;
	long int s;
	long  int l=strlen(argv[4]);
	char str[4];
	char arg[l];
	unsigned char ch;
    
	           fseek(edit_info->fptr,3,SEEK_CUR);
	           fread(&c,1,1,edit_info->fptr);
	           s=c;
	           if(l>c)
               {
		          printf("Size not enough\n");
		          return e_failure;
               }
	           char str1[s];
	           fseek(edit_info->fptr,2,SEEK_CUR);
	           int original=ftell(edit_info->fptr);
	           fread(str1,1,s,edit_info->fptr);
	           strcpy(arg,argv[4]);
	           char str2[s];
	           for(int i=0;arg[i]!='\0';i++)
	           {
		          str2[i]=arg[i];
	           }
	           for(int i=l;i<=s;i++)
	           {
		          str2[i]='!';
	           }
	           for(int i=0;i<s;i++)
        	   {
		          str1[i]=str1[i]&0;

	           }     
	           for(int i=0;i<s;i++)
	           {
		          str1[i]=str1[i]| str2[i];
	           }
	           fseek(edit_info->fptr,original,SEEK_SET);
	           fwrite(str1,1,s,edit_info->fptr);
	            return e_success;

}

Status view_edit(char *argv[],Edit *edit_info)
{
	
	edit_info->p=fopen(argv[2],"r");
	fseek(edit_info->p,10,SEEK_SET);
	char arr[4];
	unsigned char s;
	int j=0;
	int c=0;
	do
	{
		fread(arr,1,4,edit_info->p);
		if(!(strcmp(arr,"TIT2")))
		{
			fseek(edit_info->p,3,SEEK_CUR);
			fread(&s,1,1,edit_info->p);
			edit_info->song_name_size=s;
			edit_info->TIT2_song_name=malloc(edit_info->song_name_size);
			string_edit(edit_info->song_name_size,edit_info->TIT2_song_name,edit_info);
			printf("Title       : %s\n",edit_info->TIT2_song_name);
			c++;
		}
		else if(!(strcmp(arr,"TPE1")))
		{
            fseek(edit_info->p,3,SEEK_CUR);
			fread(&s,1,1,edit_info->p);
			edit_info->artist_size=s;
			edit_info->TPE1_artist=malloc(edit_info->artist_size);
			string_edit(edit_info->artist_size,edit_info->TPE1_artist,edit_info);
			printf("Artist      : %s\n",edit_info->TPE1_artist);
			c++;

		}
		else if(!(strcmp(arr,"TALB")))
		{
			fseek(edit_info->p,3,SEEK_CUR);
			fread(&s,1,1,edit_info->p);
			edit_info->album_size=s;
			edit_info->TALB_album=malloc(edit_info->album_size);
			string_edit(edit_info->album_size,edit_info->TALB_album,edit_info);
			printf("Album       : %s\n",edit_info->TALB_album);
			c++;
		}
        
		else if(!(strcmp(arr,"TYER")))
		{
			fseek(edit_info->p,3,SEEK_CUR);
			fread(&s,1,1,edit_info->p);
			edit_info->year_size=s;
			edit_info->TYER_year=malloc(edit_info->year_size);
			string_edit(edit_info->year_size,edit_info->TYER_year,edit_info);
			printf("Year        : %s\n",edit_info->TYER_year);
			c++;
		}

		else if(!(strcmp(arr,"TCOM")))
		{
			fseek(edit_info->p,3,SEEK_CUR);
			fread(&s,1,1,edit_info->p);
			edit_info->composer_size=s;
			edit_info->TCOM_composer=malloc(edit_info->composer_size);
			string_edit(edit_info->composer_size,edit_info->TCOM_composer,edit_info);
			printf("Composer    : %s\n",edit_info->TCOM_composer);
			c++;
		}
        
		else if(!(strcmp(arr,"TCON")))
		{
			fseek(edit_info->p,3,SEEK_CUR);
			fread(&s,1,1,edit_info->p);
			edit_info->genre_size=s;
			edit_info->TCON_genre=malloc(edit_info->genre_size);
			string_edit(edit_info->genre_size,edit_info->TCON_genre,edit_info);
			printf("Genre       : %s\n",edit_info->TCON_genre);
			c++;
		
		}

		else if(!(strcmp(arr,"COMM")))
		{
			fseek(edit_info->p,2,SEEK_CUR);
			fread(&s,1,1,edit_info->p);
			unsigned char x;
			fread(&x,1,1,edit_info->p);
			edit_info->comment_size=s+x;
			edit_info->COMM_comment=malloc(edit_info->comment_size);
			string_edit(edit_info->comment_size,edit_info->COMM_comment,edit_info);
			printf("Comment     : %s\n",edit_info->COMM_comment);
			c++;
		}
		else if(((strcmp(arr,"TIT2"))||(strcmp(arr,"TPE1"))||(strcmp(arr,"TALB"))||(strcmp(arr,"TCOM"))||(strcmp(arr,"TCON"))||(strcmp(arr,"TYER"))||(strcmp(arr,"COMM")))==1)
		{
			fseek(edit_info->p,3,SEEK_CUR);
			fread(&s,1,1,edit_info->p);
			long int size=s;
			fseek(edit_info->p,5,SEEK_CUR);
			fseek(edit_info->p,(size-3),SEEK_CUR);

		}
		if(c==7)
		{
			break;
		}
	}while(!feof(edit_info->p));
	fclose(edit_info->p);
	return e_success;



}
/*store only  printable characters*/
Status string_edit(long int size,char *t,Edit *edit_info)
{
	char s;
	int j=0;
	fseek(edit_info->p,2,SEEK_CUR);
	char str[size];
	for(int i=0;i<size;i++)
	{
		fread(&s,1,1,edit_info->p);
		if((s>=0x41 && s<=0x5A) ||(s>=0x61 && s<=0x7A)|| s==0x2E || (s>=0x30 && s<=0x39))
		{
			str[j]=s;
			j++;
		}
	}
	str[j]='\0';
	strcpy(t,str);

}
