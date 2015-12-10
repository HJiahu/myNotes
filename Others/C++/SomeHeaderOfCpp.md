头文件<utility>
Utility components

Pairs: objects that can hold two values of different types: pair, make_pair, piecewise_construct, piecewise_construct_t.
Generic relational operators: Standard definitions for the relational operators !=, >, <= and >= under a specific namespace: rel_ops.
Rvalue casts (C++11): Allow the generation of rvalue references: forward, move, move_if_noexcept, declval.
Generic swap function: definition used by default by the components of the standard library for all types that do not provide their own overload: swap.

Types 包含的类型
-	pair  *template <class T1, class T2> struct pair;*。 pair中有两个类型可以不一样的成员，分别时pair::first和pair::second 
	-	成员变量：first  second
	-	成员函数：构造函数，operator= ， swap（成员交换）


Pair of values (class template )
piecewise_construct_t 
Piecewise construct type (type )
Functions 包含的函数
-	swap:  Exchange values of two objects (function template )
	```
	C98:
	template <class T> void swap ( T& a, T& b )
	{
	  T c(a); a=b; b=c;
	}

	C11:
	template <class T> void swap (T& a, T& b)
	{
	  T c(std::move(a)); a=std::move(b); b=std::move(c);
	}
	template <class T, size_t N> void swap (T &a[N], T &b[N])
	{
	  for (size_t i = 0; i<N; ++i) swap (a[i],b[i]);
	}
	```

-	make_pair Construct pair object (function template )
forward 
Forward argument (function template )
move 
Move as rvalue (function template )
move_if_noexcept 
Move if noexcept (function template )
declval 
Declaration value (function template )


Constants
piecewise_construct 
Piecewise construct constant (constant )

Namespaces
rel_ops
Relational Operators (namespace )
