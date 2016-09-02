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
		vector<vector<Post>::reverse_iterator> iters = { twitters[userId].posts.rbegin(), };
		vector<vector<Post>::reverse_iterator> endIters = { twitters[userId].posts.rend(), };
		set<int> &followees = twitters[userId].followees;
		for (auto s : followees) {
			iters.push_back(twitters[s].posts.rbegin());
			endIters.push_back(twitters[s].posts.rend());
		}
		vector<int> feeds;
		for (int i = 0; i < 10; i++) {
			int maxOrder = -1;
			int maxIndex = -1;
			for (int j = 0; j < iters.size(); j++) {
				if (iters[j] != endIters[j] && maxOrder < iters[j]->order) {
					maxOrder = iters[j]->order;
					maxIndex = j;
				}
			}

			if (maxIndex == -1) {
				break;
			}
			feeds.push_back(iters[maxIndex]->id);
			iters[maxIndex]++;
		}
		return feeds;
	}

	/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
	void follow(int followerId, int followeeId) {
		if (followeeId == followerId) {
			return;
		}
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
	int counter = 0;
};

/**
* Your Twitter object will be instantiated and called as such:
* Twitter obj = new Twitter();
* obj.postTweet(userId,tweetId);
* vector<int> param_2 = obj.getNewsFeed(userId);
* obj.follow(followerId,followeeId);
* obj.unfollow(followerId,followeeId);
*/