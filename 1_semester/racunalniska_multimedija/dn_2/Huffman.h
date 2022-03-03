#pragma once
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <optional>

#include "Utils.h"

class Huffman
{
private:
	struct Node {
		std::pair<std::optional<unsigned char>, float> p;
		Node* left, *right;

		Node(std::pair<std::optional<unsigned char>, float> pa) {
			p = pa;
			left = NULL;
			right = NULL;
		}
	};

	struct compare {
		bool operator()(Node* l, Node* r) {
			return l->p.second > r->p.second;
		};
	};

	void makeCodes(std::map<unsigned char, std::vector<bool>>& v, struct Node* root, std::vector<bool> b) {
		if (!root) {
			return;
		}

		if (root->p.first) {
			//v.push_back(std::make_pair<char, int>(root->p.first, root->p.second));
			v.insert(std::pair<unsigned char, std::vector<bool >>(*root->p.first, b));
		}
		std::vector<bool> b0 = b;
		std::vector<bool> b1 = b;

		b0.push_back(false);
		b1.push_back(true);

		makeCodes(v, root->left, b0);
		makeCodes(v, root->right, b1);
	}

	//std::vector<std::pair<char, int>> sortedVectorOfValues(std::map<char, int> mp);
	std::map<unsigned char, std::vector<bool>> buildTree(std::map<unsigned char, float> v) {
		std::map<unsigned char, std::vector<bool>> mp;

		std::priority_queue<Node*, std::vector<Node*>, compare> prior_q;
		
		Node* l, * r, *top;
		for (auto &pair : v) {
			if (pair.second != 0) {
				prior_q.push(new Node(pair));
			}
		}

		while (prior_q.size() != 1) {
			l = prior_q.top();
			prior_q.pop();

			r = prior_q.top();
			prior_q.pop();

			top = new Node(std::make_pair<std::optional<unsigned char>, float>({}, l->p.second + r->p.second));

			top->left = l;
			top->right = r;


			prior_q.push(top);
		}
		
		std::vector<bool> b;
		makeCodes(mp, prior_q.top(), b);

		return mp;
	}
	//std::map<char, std::vector<bool>> buildTreeDecompression(std::map<char, float> v);
	std::map<unsigned char, float> calculateProbability(std::map<unsigned char, int> mp, int size) {
		std::map<unsigned char, float> cf;

		for (auto &p : mp) {
			if (p.second != 0) {
				cf.insert(std::pair<unsigned char, float>(p.first, static_cast<float>(static_cast<double>(p.second) / size)));
			}
		}
		//for (auto p : tree) {
		//	cf.insert(std::pair<char, float>(p.first, static_cast<float>(mp[p.first]) / tree.size()));
		//}

		return cf;
	}

public:
	std::tuple<std::map<unsigned char, std::vector<bool>>, std::map<unsigned char, float>> Encode(std::vector<unsigned char> v) {
		//std::vector<bool> b;

		std::map<unsigned char, int> mp = Utils::commonDictionaryMap();

		for (auto c : v) {
			//std::map<char, int>::iterator it = std::find(mp.begin(), mp.end(), c);
			mp[c]++;
		}

		std::map<unsigned char, float> cf = calculateProbability(mp, v.size());

		std::map<unsigned char, std::vector<bool>> tree = buildTree(cf);

		return std::tuple<std::map<unsigned char, std::vector<bool>>, std::map<unsigned char, float>>(tree, cf);
	}


	std::vector<unsigned char> Decode(std::vector<bool> data, std::map<unsigned char, float> cf) {
		std::vector<unsigned char> c;

		std::map<unsigned char, std::vector<bool>> tree = buildTree(cf);

		std::vector<bool> bols;
		for (auto b : data) {
			bols.push_back(b);
			
			for (std::map<unsigned char, std::vector<bool>>::iterator it = tree.begin(); it != tree.end(); ++it) {
				
				if (it->second.size() == bols.size() and std::equal(it->second.begin(), it->second.end(), bols.begin())) {
					c.push_back(it->first);
					bols.clear();
					break;
				}
			}
		}

		return c;
	}
};

