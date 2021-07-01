#pragma once

#include <string>
#include <vector>

/** A class used to represent a Playlist */

class VideoPlaylist {
 private:
  std::vector<std::vector<std::string>> Playlists;


 public:
  VideoPlaylist(std::vector<std::vector<std::string>>&& Playlists);

  // Returns all the playlists.
  const std::vector<std::vector<std::string>>& getPlaylists() const;

//   // Returns the video id of the video.
//   const std::string& getVideoId() const;

//   // Returns a readonly collection of the tags of the video.
//   const std::vector<std::string>& getTags() const;
};

