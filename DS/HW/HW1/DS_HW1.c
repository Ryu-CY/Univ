// �ڷᱸ�� ���� 1: ����ü ���� �� ���

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct song
{
	char artist[20];
	char title[20];
} Song;

typedef struct playlist
{
	int no_of_songs;
	Song song_list[3];
} Playlist;

int main()
{
	Playlist my_playlist;
	int num = 0;

	my_playlist.no_of_songs = 0;
	
	strcpy(my_playlist.song_list[0].artist, "��Ʈ");
	strcpy(my_playlist.song_list[0].title, "Ribbon");

	strcpy(my_playlist.song_list[1].artist, "IU");
	strcpy(my_playlist.song_list[1].title, "�ð��� �ٱ�");

	strcpy(my_playlist.song_list[2].artist, "������");
	strcpy(my_playlist.song_list[2].title, "�Ƹ���� ��������");

	printf("No		Artist			Title\n");

	for (int i = 0; i < 3; i++)
	{
		my_playlist.no_of_songs++;

		printf("%d.		%s			%s\n", my_playlist.no_of_songs, my_playlist.song_list[num].artist, my_playlist.song_list[num].title);

		num++;
	}
	printf("A total number of songs in the list: %d\n", my_playlist.no_of_songs);

	return 0;
}