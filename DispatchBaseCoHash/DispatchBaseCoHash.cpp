//============================================================================
// Name        : DispatchBaseCoHash.cpp
// Author      : dragonlan
// Version     : 1.0
// Copyright   : Copyright dragonlan
// Description : CoHash in C++, Ansi-style, for practice
//============================================================================

#include <iostream>
#include <set>
#include <vector>
#include <time.h>
#include <cstdlib>

#include "DispatchBaseCoHash.h"

using namespace std;
namespace UniformHash{
template <class T>
const _server<T>* UniformHashHandle<T>::getServer(unsigned int key)
{
	if(_arrvnode_sorted.empty())
	{
		return NULL;
	}
	_vnode obj;
	obj.hash_val = key;
    typename vector<_vnode>::const_iterator iter = std::lower_bound(_arrvnode_sorted.begin(), _arrvnode_sorted.end(), obj);

    if (iter == _arrvnode_sorted.end())
    {
    	iter = _arrvnode_sorted.begin();
    }

    return iter->psvr;
}

template <class T>
int UniformHashHandle<T>::IsSameServer(const _server<T> &s, const _server<T> &d)
{
	return (s._ipstr == d._ipstr) &&
			(s._port == d._port) &&
			(s._vnodecnt == d._vnodecnt);
}

template <class T>
int UniformHashHandle<T>::IsDiff(const std::set<_server<T> > &s, const std::set<_server<T> > &d)
{
	if (s.size() != d.size())
	{
		return true;
	}

	for(typename std::set<_server<T> >::const_iterator it = s.begin(); it != s.end(); it++)
	{
		typename std::set<_server<T> >::const_iterator it2 = d.begin();
		for( ;it2 != d.end(); it2++)
		{
			if (IsSameServer(*it, *it2)) break;
		}
		if(it2 == d.end())
		{
			return true;
		}
	}

	return false;
}
template <class T>
int UniformHashHandle<T>::updateUniformHash(const std::set<_server<T> > &newservers)
{
	if (checkInterval > time(NULL) - _last_update_time)
	{
		return 0;
	}

	return UniformHashInit(newservers);
}

template <class T>
int UniformHashHandle<T>::UniformHashInit(const std::set<_server<T> > &newservers)
{
	_last_update_time = time(NULL);

	if (!IsDiff(_servers, newservers))
	{
		//same server and vnodecnt
		return 0;
	}
	//server change, recreate hash circle
	_servers = newservers;
	_arrvnode_sorted.clear();

	for(typename set<_server<T> >::const_iterator itr = _servers.begin();itr != _servers.end();itr++)
	{
		for(int i=0; i < itr->_vnodecnt; i++)
		{
			_vnode t;
			t.hash_string = itr->_ipstr + ":" + to_string(itr->_port) + ":" + to_string(i);
			t.hash_val = JSHash(t.hash_string.c_str(), t.hash_string.length());
			t.psvr = &(*itr);

			_arrvnode_sorted.push_back(t);
		}
	}

	std::sort(_arrvnode_sorted.begin(), _arrvnode_sorted.end());
	return 0;
}
};
int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	srand(time(NULL));

	std::set< UniformHash::_server<int> > newservers;
	for (int i = 0; i<100;i++)
	{
		struct UniformHash::_server<int> t;
		t._ipstr = to_string(i) + "." + to_string(i) + "." + to_string(i) + "." + to_string(i);
		t._port = 80;
		t._vnodecnt = 100;
		newservers.insert(t);
	}
	class UniformHash::UniformHashHandle<int> uniforHashHandle;

	uniforHashHandle.UniformHashInit(newservers);

	for(int i = 0; i < 10; i++ )
	{
		int key = rand();
		cout <<"key:"<<key<<" server:" <<uniforHashHandle.getServer(key)->_ipstr<<endl;
	}

	return 0;
}

//};

