#include "BASE functions.h"

void deleteTrack(TRACK **playlist, TRACK *track) {
	if (track == *playlist) {
		*playlist = track->next;
	}
	track->prev->next = track->next;
	track->next->prev = track->prev;
	free(track);
}

TRACK *setPlaylist(TRACK *playlist) {
	return playlist;
}

TRACK *changePlaylist(TRACK *playlist) {
	
	return playlist;
}

TRACK *deletePlaylist(TRACK *playlist) {
	TRACK *track = playlist->next;
	playlist->prev->next = NULL;
	while (playlist != NULL) {
		free(playlist);
		playlist = track;
		if (track != NULL) {
			track = track->next;
		}
	}
	return NULL;
}
