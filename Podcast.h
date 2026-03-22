//
// Created by Christopher Vaughn on 10/24/25.
//

#ifndef CIRCULARTEMPLATEDLIST_PODCAST_H
#define CIRCULARTEMPLATEDLIST_PODCAST_H

#include <iostream>
#include "Media.h"

// Represents a podcast episode, showing how multiple types can share the list.
class Podcast : public Media {
private:
    // 'episodeTitle' was removed; we now use 'title' from the Media base class.
    std::string host;
    int episodeNumber;
public:
    // Constructor now initializes the base class and its own members.
    Podcast(const std::string& t, const std::string& h, int d)
    : Media(t, 0), host(h), episodeNumber(d) {}

    // Override toString() from the Media base class.
    std::string toString() const override;

    // Override play() to provide Podcast-specific behavior.
    void play() const override;
};

#endif //CIRCULARTEMPLATEDLIST_PODCAST_H