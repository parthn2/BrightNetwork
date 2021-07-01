#include "videoplayer.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// #include <boost/algorithm/string.hpp>    //for Case sensivity issue

int case_insensitive_match(std::string s1, std::string s2) {
   //convert s1 and s2 into lower case strings
   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
   if(s1.compare(s2) == 0)
      return 1; //The strings are same
   return 0; //not matched
}

void VideoPlayer::numberOfVideos() {
  std::cout << mVideoLibrary.getVideos().size() << " videos in the library"
            << std::endl;
}

void VideoPlayer::showAllVideos() {
  std::cout << "Here's a list of all available videos:" << std::endl;
  std::vector<Video> Videos = mVideoLibrary.getVideos();
  std::sort(Videos.begin(), Videos.end(), [ ]( const Video& lhs, const Video& rhs )
  {
    return lhs.getTitle() < rhs.getTitle();
  });
  std::string space = "";
  for(Video i : Videos) 
  {
    std::string space = "";
    std::vector<std::string> Tags = i.getTags();
    std::cout << i.getTitle() << " (" << i.getVideoId() << ") [";
    for (auto i: Tags)
    {
      std::cout << space << i;
      space = " ";
    }
    std::cout<< "]\n";
  }
}

 
 void VideoPlayer::playVideo(const std::string& videoId) {
  std::vector<Video> Videos = mVideoLibrary.getVideos();
  int ifVideo = 0;
  for(Video i : Videos)
  {
    if(videoId == i.getVideoId())
    {
      if(isVideoPlaying == 1)
      {
        std::cout << "Stopping video: " << playingVideoTitle << "\n";
      }
      std::cout << "Playing video: " << i.getTitle() << "\n";
      ifVideo = 1;
      isVideoPlaying = 1;
      isVideoPaused = 0;
      playingVideoTitle = i.getTitle();
    }
  }
  if(ifVideo == 0)
  {
    std::cout << "Cannot play video: " <<  "Video does not exist" << "\n";
  }
}

void VideoPlayer::stopVideo() {
  if(isVideoPlaying == 0)
  {
    std::cout << "Cannot stop video: No video is currently playing" << "\n";
  }
  else
  {
    std::cout << "Stopping video: " << playingVideoTitle << "\n";
    isVideoPlaying = 0;
    playingVideoTitle = "";
  }
}

void VideoPlayer::playRandomVideo() {
  std::vector<Video> Videos = mVideoLibrary.getVideos();
  int randomNumber = rand() % mVideoLibrary.getVideos().size();

  VideoPlayer::playVideo(Videos[randomNumber].getVideoId());
}

void VideoPlayer::pauseVideo() {
  if(isVideoPlaying == 0)
  {
    std::cout << "Cannot pause video: No video is currently playing" << "\n";
    return;
  }
  if(isVideoPaused == 1)
  {
    std::cout << "Video already paused: " << playingVideoTitle << "\n";
  }
  else
  {
    std::cout << "Pausing video: " << playingVideoTitle << "\n";
    isVideoPaused = 1;
  }

}

void VideoPlayer::continueVideo() {
  if(isVideoPlaying == 0)
  {
    std::cout << "Cannot continue video: No video is currently playing" << "\n";
  }
  else if(isVideoPaused == 0)
  {
    std::cout << "Cannot continue video: Video is not paused" << "\n";
  }
  else
  {
    std::cout << "Continuing video: " << playingVideoTitle << "\n";
    isVideoPaused = 0;
  }
}

void VideoPlayer::showPlaying() {
  if(isVideoPlaying == 0)
  {
    std::cout << "No video is currently playing" << "\n";
    return;
  }
  std::cout<< "Currently playing: ";
  std::vector<Video> Videos = mVideoLibrary.getVideos();
  for(Video i : Videos) 
  {
    std::vector<std::string> Tags = i.getTags();
    if(playingVideoTitle == i.getTitle())
    {
      std::string space = "";
      std::cout << i.getTitle() << " (" << i.getVideoId() << ") [";
      for (auto i: Tags)
      {
        std::cout << space << i;
        space = " ";
      }
      std::cout<< "]";
      if(isVideoPaused == 1)
      {
        std:: cout << " - PAUSED";
      }
      std::cout << "\n";
    }
  }
}

void VideoPlayer::createPlaylist(const std::string& playlistName) {
  int doPlaylistNameExists = 0;
  for(int i = 0; i < Playlists.size() ; i++)
  {
    if(case_insensitive_match(Playlists[i][0], playlistName))
    {
      doPlaylistNameExists = 1;
    }
  }
  if(doPlaylistNameExists == 1)
  {
    std::cout << "Cannot create playlist: A playlist with the same name already exists" << "\n";
  }
  else
  {
    std::vector<std::string> tempVec = {playlistName};
    Playlists.push_back(tempVec);
    std::cout << "Successfully created new playlist: " << playlistName << "\n";
  }
}

void VideoPlayer::addVideoToPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  int doPlaylistNameExists = 0;
  std::vector<Video> Videos = mVideoLibrary.getVideos();
  for(int i = 0; i < Playlists.size() ; i++)
  {
    if(case_insensitive_match(Playlists[i][0], playlistName))
    {
      int isVideoAlreadyAdded = 0;
      for(int a = 1; a < Playlists[i].size() ; a++)
      {
        if(case_insensitive_match(Playlists[i][a], videoId))
        {
          isVideoAlreadyAdded = 1;
        }
      }
      if(isVideoAlreadyAdded == 1)
      {
        std::cout << "Cannot add video to " <<  playlistName << ": Video already added" << "\n"; 
      }
      else
      {
        int isVideoAvailible = 0;
        for(Video k : Videos) 
        {
          if(case_insensitive_match(k.getVideoId(), videoId))
          {
            std::string temp = "";
            for(Video k2 : Videos)
            {
              if(k2.getVideoId() == videoId)
              {
                temp =  k2.getTitle();
              }
            }
            std::cout << "Added video to " << playlistName << ": " << temp <<"\n";
            Playlists[i].push_back(k.getVideoId());
            isVideoAvailible = 1;
            break;
          }
        }
        if(isVideoAvailible == 0)
        {
          std::cout << "Cannot add video to " << playlistName <<": Video does not exist" << "\n"; 
        }
      }
      doPlaylistNameExists = 1;
    }
  }
  if(doPlaylistNameExists == 0)
  {
    std::cout << "Cannot add video to " << playlistName << ": Playlist does not exist" << "\n";
  }
}

void VideoPlayer::showAllPlaylists() {
  int ifPlaylistExists = 0;
  for(int i=0;i < Playlists.size();i++)
  {
    ifPlaylistExists = 1;
  }
  if(ifPlaylistExists == 0)
  {
    std::cout << "No playlists exist yet" <<"\n";
  }
  else
  {
    std::cout << "Showing all playlists:" << "\n";
    for(int i=0;i < Playlists.size();i++)
    {
      std::cout << Playlists[i][0] << "\n";
      ifPlaylistExists = 1;
    }
  }
}

void VideoPlayer::showPlaylist(const std::string& playlistName) {
  int doPlaylistNameExists = 0;
  std::vector<Video> Videos = mVideoLibrary.getVideos();
  for(int i = 0; i < Playlists.size() ; i++)
  {
    if(case_insensitive_match(Playlists[i][0], playlistName))
    {
      std::cout << "Showing playlist: " << playlistName << "\n";
      if(Playlists[i].size() == 1)
      {
        std::cout << "No videos here yet" << "\n";
      }
      else
      {
        for(int a =0; a < Playlists[i].size() ; a++)
        {
          for(Video k2 : Videos) 
          {
            std::vector<std::string> Tags = k2.getTags();
            if(Playlists[i][a] == k2.getVideoId())
            {
              std::string space = "";
              std::cout << k2.getTitle() << " (" << k2.getVideoId() << ") [";
              for (auto k3: Tags)
              {
                std::cout << space << k3;
                space = " ";
              }
              std::cout<< "]";
              std::cout << "\n";
            }
          }
        }
      }
      doPlaylistNameExists = 1;
    }
  }
  if(doPlaylistNameExists == 0)
  {
    std::cout << "Cannot show playlist " << playlistName << ": Playlist does not exist" <<"\n";
  }
}

void VideoPlayer::removeFromPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  std::vector<Video> Videos = mVideoLibrary.getVideos();
  int doVideoExists = 0;
  for(Video i : Videos) 
  {
    if(i.getVideoId() == videoId)
    {
      doVideoExists = 1;
    }
  }
  int doPlaylistNameExists = 0;
  for(int i = 0; i < Playlists.size() ; i++)
  {
    if(case_insensitive_match(Playlists[i][0], playlistName))
    {
      doPlaylistNameExists = 1;
      if(Playlists[i].size() == 1)
      {
        std::cout << "Cannot remove video from " << playlistName << ": Video is not in playlist" <<"\n";
      }
      else
      {
        if(doVideoExists == 0)
        {
          break;
        }
        std::string VideoName = "";
        std::vector<std::string>::iterator position = std::find(Playlists[i].begin(), Playlists[i].end(), videoId);
        if (position != Playlists[i].end()) 
        {
            Playlists[i].erase(position); 
              for(Video k : Videos)
              {
                if(videoId == k.getVideoId())
                {
                  VideoName = k.getTitle();
                }
              }
            std::cout << "Removed video from " << playlistName  << ": "  << VideoName << "\n";
        }
      }
    }
  }
  if(doPlaylistNameExists == 0)
  {
    std::cout << "Cannot remove video from " << playlistName << ": Playlist does not exist" <<"\n";
    return;
  }
  if(doVideoExists == 0)
  {
    std::cout << "Cannot remove video from " << playlistName << ": Video does not exist" <<"\n";
    return;
  }
}

void VideoPlayer::clearPlaylist(const std::string& playlistName) {
  int doPlaylistExists = 0;
  for(int i=0;i < Playlists.size(); i++)
  {
    if(Playlists[i][0] == playlistName)
    {
      Playlists.erase(Playlists.begin()+i);
      Playlists.push_back({playlistName});
      doPlaylistExists = 1;
      std::cout << "Successfully removed all videos from " << playlistName << "\n" ;
    }
  }
  if(doPlaylistExists == 0)
  {
    std::cout << "Cannot clear playlist " << playlistName << ": Playlist does not exist" << "\n" ;
  }
}

void VideoPlayer::deletePlaylist(const std::string& playlistName) {
  int doPlaylistExists = 0;
  for(int i=0;i < Playlists.size(); i++)
  {
    if(case_insensitive_match(Playlists[i][0], playlistName))
    {
      Playlists.erase(Playlists.begin()+i);
      doPlaylistExists = 1;
      std:: cout << "Deleted playlist: " << playlistName << "\n" ;
    }
  }
  if(doPlaylistExists == 0)
  {
    std::cout << "Cannot delete playlist " << playlistName << ": Playlist does not exist" << "\n" ;
  }
}

inline bool caseInsCharCompSingle(char a, char b) {
   return(toupper(a) == b);
}

std::string::const_iterator caseInsFind(std::string& s, const std::string& p) {
   std::string tmp;

   transform(p.begin(), p.end(),             // Make the pattern
             back_inserter(tmp),                 // upper-case
             toupper);

   return(search(s.begin(), s.end(),         // Return the iter- 
                 tmp.begin(), tmp.end(),     // ator returned by
                 caseInsCharCompSingle));        // search
}

bool check_number(std::string str) {
   for (int i = 0; i < str.length(); i++)
   if (isdigit(str[i]) == false)
      return false;
      return true;
}

void VideoPlayer::searchVideos(const std::string& searchTerm) {

  std::vector<Video> Videos = mVideoLibrary.getVideos();
  int numberfound = 1;
  std::sort(Videos.begin(), Videos.end(), [ ]( const Video& lhs, const Video& rhs )
  {
    return lhs.getTitle() < rhs.getTitle();
  });
  std::map<int, std::string> mp;
  for(Video i: Videos) 
  {
    std::string temp = i.getTitle();
       std::string::const_iterator it = caseInsFind(temp, searchTerm);
      if (it != temp.end()) {
          numberfound++;
      }
  }
  if(numberfound > 1)
  {
    std::cout << "Here are the results for "  << searchTerm << ":" << "\n"; 
  }
  numberfound = 1;
  for(Video i: Videos) 
  {
    std::string temp = i.getTitle();
       std::string::const_iterator it = caseInsFind(temp, searchTerm);
      if (it != temp.end()) {
          std::cout << numberfound <<") " ;
          std::string space = "";
          std::vector<std::string> Tags = i.getTags();
          std::cout << i.getTitle() << " (" << i.getVideoId() << ") [";
          for (auto i: Tags)
          {
            std::cout << space << i;
            space = " ";
          }
          std::cout<< "]\n";
          mp[numberfound] = i.getVideoId();
          numberfound++;
      }
    }
  if(numberfound == 1)
  {
    std::cout << "No search results for " << searchTerm << "\n" ;
    return;
  }
  std::cout << "Would you like to play any of the above? If yes, specify the number of the video." << "\n";
  std::cout << "If your answer is not a valid number, we will assume it's a no." << "\n";
  std::string n;
  std::cin >> n;
  if(check_number(n))
  {
    int k = stoi(n);
    if( k < numberfound)
    {
      const std::string temp= mp[k];
      VideoPlayer::playVideo(temp);
    }
  }
}

void VideoPlayer::searchVideosWithTag(const std::string& videoTag) {
  std::cout << "searchVideosWithTag needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId, const std::string& reason) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::allowVideo(const std::string& videoId) {
  std::cout << "allowVideo needs implementation" << std::endl;
}
