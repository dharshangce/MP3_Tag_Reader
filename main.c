#include <stdio.h>
#include <string.h>
#include "info.h"

int main(int argc,char *argv[])
{
  Info info;
  Edit edit_info;

	if(argc>=2 && argc<=3)
	  {
		  if(!(strcmp(argv[1],"-v")))
		  {
			  if(read_validate(argv,&info)==e_success)
			  {
				  printf("Read and validate success\n");

			  }
			  else
			  {
				  printf("Read and validate failure\n");
				  return e_failure;
			  }
			  if(view(&info)==e_success)
			  {
				  //print(&info);
				  printf("Extracting the Album art. Done\n");

			  }
			  else
			  {
				  printf("Extracting the Album art. failure\n" );
				  return e_failure;

			  }
			
		  }
	
		else if(argc=2)
          {
	      if(!(strcmp(argv[1],"--help")))
	      {
		      printf("Help menu for Mp3 Tag Reader and Editior:\n");
		      printf("For viewing the tag-          %s -v <.mp3 file>\n",argv[0]);
		      printf("For editing the tag-          %s -e <.mp3 file> <modifier> <tag>\n\n",argv[0]);
			  printf("Modifier           Function\n");
		      printf("  -t               Modifies Title tag\n");
		      printf("  -a               Modifies Artist tag\n");
		      printf("  -A               Modifies Album tag\n");
		      printf("  -y               Modifies Year tag\n");
		      printf("  -c               Modifies Comment tag\n");
			  printf("  -C               Modofies Composer tag\n");
		      printf("  -g               Modifies Genre tag\n");
		      printf("\n---------------------------------------------------------------------------\n");

	     }
	     else
	     {
		  printf("ERROR: %s : INVALID ARGUMENTS\nUSAGE :\n",argv[0]);
          printf("To get help pass like    : %s --help\n",argv[0]);
		  return e_failure;
	  
	     }
        }
	 }
	else if(argc==5)
	{
		char tag[5];
		if(!strcmp(argv[1],"-e"))
		{
			if(read_validate_edit(argv,&edit_info)==e_success)
			{
				printf("Read and validate edit success\n");
				if(!(strcmp(argv[3],"-t")))
				{
					strcpy(tag,"TIT2");
				
				}
				else if(!(strcmp(argv[3],"-a")))
				{
					strcpy(tag,"TPE1");
				}
				else if(!(strcmp(argv[3],"-A")))
				{
					strcpy(tag,"TALB");
					
				}
                else if(!(strcmp(argv[3],"-y")))
				{
					strcpy(tag,"TYER");
				}
				else if(!(strcmp(argv[3],"-c")))
				{
					strcpy(tag,"COMM");
				}
				else if(!(strcmp(argv[3],"-g")))
				{
					strcpy(tag,"TCON");
				}
				else if(!(strcmp(argv[3],"-C")))
				{ 
					strcpy(tag,"TCOM");

				}
				else
				{
					printf("Tag Not Matched\n");
					return e_failure;
				}
			}
			else
			{
				printf("Read and validate edit failure\n");
				return e_failure;
			}
			if(edit(argv,tag,&edit_info)==e_success)
			{
				if(view_edit(argv,&edit_info)==e_success)
				{
					printf("Modification Done \n");
					return e_success;

				}

			}
			else
			{
				printf("Edit Failure\n");
				return e_failure;
			}
		}


	}
    
   else
   {
	  printf("---------------------------------------------------------------------------------------\n\n");
	  printf("ERROR: %s : INVALID ARGUMENTS\nUSAGE :\n",argv[0]);
	  printf("To get help pass like         %s --help\n",argv[0]);
      printf("For viewing the tag-          %s -v <.mp3 file>\n",argv[0]);
	  printf("For editing the tag-          %s -e <.mp3 file> <modifier> <tag>\n\n",argv[0]);
	  printf("Modifier           Function\n");
	  printf("  -t               Modifies Title tag\n");
	  printf("  -a               Modifies Artist tag\n");
	  printf("  -A               Modifies Album tag\n");
	  printf("  -y               Modifies Year tag\n");
	  printf("  -c               Modifies Comment tag\n");
      printf("  -g               Modifies Genre tag\n");
	  printf("----------------------------------------------------------------------------------------\n");

  }
  return 0;
}

