//============================================================================
// Name        : DispatchBaseCoHash.h
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

#include "MurmurHash3.h"

using namespace std;



namespace UniformHash{
template <class T>
struct _server {
	inline bool operator <(const _server & s) const
	{
		if(_ipstr == s._ipstr)
		{
			if (_port == s._port)
			{
				return _vnodecnt < s._vnodecnt;
			}
			return _port < s._port;
		}
		return _ipstr.compare(s._ipstr);
	}

	string _ipstr;
	int		_port;
	int		_vnodecnt;

	T		_data;
};
const int checkInterval = 10;//check ervery 10sec

template <class T>
class UniformHashHandle{
public:
	UniformHashHandle():_last_update_time(0), _servers(){}
	int UniformHashCircleRefresh(const std::set<_server<T> > &newservers);

	const _server<T>* getServer(unsigned int key);

	int updateUniformHash(const std::set<_server<T> > &newservers);
	int IsSameServer(const _server<T> &s, const _server<T> &d);
	int IsDiff(const std::set<_server<T> > &s, const std::set<_server<T> > &d);

	inline unsigned int MyHash(const char * str, int len){
		unsigned int hash = 1315423911;
		for (size_t i = 0; i < len; i++)
		{
			hash = ((hash^str[i])<<8) + (str[i]*131313)%13131;
			hash ^= ((hash << 5) + (hash >> 2));
		};
		return hash;
	};
	inline uint32_t MurmurHash32(const char *str, size_t len)
	{
	    uint32_t val;
	    MurmurHash3_x86_32(str, len, 0, &val);
	    return val;
	}

private:
	struct _vnode{
		_vnode():hash_val(0),psvr(NULL){}

		inline bool operator <(const _vnode & rhs) const
		{
			return this->hash_val < rhs.hash_val;
		}
		unsigned int hash_val;
		string hash_string;
		const _server<T>* psvr;
	};
private:
	time_t 	_last_update_time;
	set<_server<T> > _servers;
	vector<_vnode> _arrvnode_sorted;
};

}
