#ifndef INFO_H
#define INFO_H


typedef enum
{
	e_success,
	e_failure,
}Status;


typedef struct _INFO
{
	char *song_name_TIT2;
	char *artist_TPE1;
	char *album_TALB;
	char *year;
	char *genre_TCON;
	char *comment_COMM;
	char *composer_TCOM;

	FILE *fp;
	long int file_size;
	long int size_song_name;
	long int size_artist;
	long int size_year;
	long int size_album;
	long int size_comment;
	long int size_genre;
	long int size_composer;
}Info;


typedef struct _Edit
{
   char *TIT2_song_name;
   char *TPE1_artist;
   char *TALB_album;
   char *TYER_year;
   char *TCON_genre;
   char *COMM_comment;
   char *TCOM_composer;
	FILE *fptr;
	FILE *p;
	long int  size_file;
	long int song_name_size;
	long int artist_size;
	long int year_size;
	long int album_size;
	long int comment_size;
	long int genre_size;

	long int composer_size;
}Edit;
/* To view the contents*/
Status read_validate(char *argv[],Info *info);
char string(long int,char *,Info *info);
Status view(Info *info);



/*To edit the contents*/
Status edit(char *argv[],char *tag,Edit *edit_info);
Status read_validate_edit(char *argv[],Edit *edit_info);
Status operation(Edit *edit_info,char *argv[],char **fpt);
Status view_edit(char *argv[],Edit *edit_info);
Status string_edit(long int ,char *,Edit *edit_info);

#endif
