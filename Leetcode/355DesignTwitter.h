#pragma once
#include "common.h"

class Twitter {
public:
	/** Initialize your data structure here. */
	Twitter() {

	}

	/** Compose a new tweet. */
	void postTweet(int userId, int tweetId) {
		twitters[userId].posts.push_back({ counter++, tweetId });
	}

	/** Retrieve the 10 most recent tweet ids in the user's news feed. 
	    Each item in the news feed must be posted by users who the user followed or by the user herself. 
		Tweets must be ordered from most recent to least recent. 
	**/
	vector<int> getNewsFeed(int userId) {

	}

	/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
	void follow(int followerId, int followeeId) {
		twitters[followerId].followees.insert(followeeId);
	}

	/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
	void unfollow(int followerId, int followeeId) {
		twitters[followerId].followees.erase(followeeId);
	}

private:
	struct Post {
		int order;
		int id;
	};
	struct User {
		vector<Post> posts;
		set<int> followees;
	};
	map<int, User> twitters;
	int counter;
};

/**
* Your Twitter object will be instantiated and called as such:
* Twitter obj = new Twitter();
* obj.postTweet(userId,tweetId);
* vector<int> param_2 = obj.getNewsFeed(userId);
* obj.follow(followerId,followeeId);
* obj.unfollow(followerId,followeeId);
*/
