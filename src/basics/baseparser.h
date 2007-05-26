
#ifndef __BASEPARSER_H__
#define __BASEPARSER_H__


#include "basetypes.h"
#include "baseobjects.h"
#include "basesafeptr.h"
#include "basememory.h"
#include "basealgo.h"
#include "basetime.h"
#include "basestring.h"
#include "baseexceptions.h"
#include "basearray.h"


NAMESPACE_BEGIN(basics)

//
// Symbol Types
//
#define SymbolTypeNonterminal		0
#define SymbolTypeTerminal			1
#define SymbolTypeWhitespace		2
#define SymbolTypeEnd End Character	3
#define SymbolTypeCommentStart		4
#define SymbolTypeCommentEnd		5
#define SymbolTypeCommentLine		6
#define SymbolTypeError				7

#define EEOF 512

//
// Initial Buffer Sizes - Paul Hulskamp
//
#define STACK_SIZE 64
#define TOKEN_SIZE 32
#define RT_BUFF_SIZE 128
#define RT_INDEX_SIZE 32


// predeclarations

class CParser;
class CParseInput;
class CParseConfig;


class CSymbol : public defaultcmp
{
public:
	short		idx;
	short		Type;
	string<>	Name;

	CSymbol() : idx(0),Type(0)
	{}
	~CSymbol()
	{}
	CSymbol(const CSymbol& s) : idx(s.idx),Type(s.Type),Name(s.Name)
	{}
	const CSymbol& operator=(const CSymbol& s)
	{
		idx=s.idx;
		Type=s.Type;
		Name=s.Name;
		return *this;
	}
	void clear()
	{
		idx=0;
		Type=0;
		Name.clear();
	}
};

class CRule : public defaultcmp
{
public:
	short				NonTerminal;
	//TArrayDST<short>	cSymbol;
	vector<short>		cSymbol;

	CRule() : NonTerminal(0)	{}
	~CRule()					{}
};
class CEdge : public defaultcmp
{
public:
	short	CharSetIndex;
	short	TargetIndex;
	CEdge() : CharSetIndex(0),TargetIndex(0) {}
	~CEdge()	{}
};
class CDFAState : public defaultcmp
{
public:
	char				Accept;
	short				AcceptIndex;
	//TArrayDST<CEdge>	cEdge;
	vector<CEdge>		cEdge;

	CDFAState() : Accept(0),AcceptIndex(0)	{}
	~CDFAState()	{}
};
class CAction : public defaultcmp
{
public:
	short SymbolIndex;
	short Action;
	short Target;
	CAction() : SymbolIndex(0),Action(0),Target(0)	{}
	~CAction()	{}

};
class CLALRState : public defaultcmp
{
public:
	//TArrayDST<CAction>	cAction;
	vector<CAction>	cAction;
	CLALRState()	{}
	~CLALRState()	{}

};
class CToken : public defaultcmp
{
public:
	short			id;
	string<>		cLexeme;
	unsigned int	line;
	unsigned int	column;

	CToken() : id(0),line(0),column(0)	{}
	CToken(short i) : id(i), line(0),column(0)	{}
	CToken(short i, const string<>& s)
		: id(i), cLexeme(s),line(0),column(0)	{}
	~CToken()	{}

	void clear()
	{
		id=0;
		cLexeme.clear();
	}

	CToken(const CToken& t)
		: id(t.id), cLexeme(t.cLexeme),line(t.line),column(t.column)
	{}
	const CToken& operator=(const CToken& t)
	{
		id=t.id;
		cLexeme=t.cLexeme;
		line=t.line;
		column=t.column;
		return *this;
	}

};

class CStackElement : public defaultcmp
{
public:
	CSymbol		symbol;
	CToken		cToken;
	short		state;
	short		rule;

	size_t cChildPos;
	size_t cChildNum;

	CStackElement()
		: state(0),rule(0)
		,cChildPos(0), cChildNum(0)
	{}
	~CStackElement()	{}

	CStackElement(const CStackElement& se)
		: symbol(se.symbol), cToken(se.cToken),state(se.state),rule(se.rule)
		,cChildPos(se.cChildPos),cChildNum(se.cChildNum)
	{}
	const CStackElement& operator=(const CStackElement& se)
	{
		symbol=se.symbol;
		cToken=se.cToken;
		state=se.state;
		rule=se.rule;
		cChildPos = se.cChildPos;
		cChildNum = se.cChildNum;
		return *this;
	}

	void clear()
	{
		symbol.clear();
		cToken.clear();
		state=0;
		rule=0;
		cChildPos = 0;
		cChildNum = 0;
	}

};


class CParseInput : public allocator_r_dy<char>
{
	ICL_EMPTY_COPYCONSTRUCTOR(CParseInput)
public:
	///////////////////////////////////////////////////////////////////////////
	// position marker
	unsigned int	line;
	unsigned int	column;

	CParseInput()
		: line(1),column(1)
	{}
	CParseInput(size_t sz)
		: allocator_r_dy<char>(sz), line(1),column(1)
	{}
	virtual ~CParseInput()
	{}

	void init()
	{
		this->line =1;
		this->column =1;
	}

	short scan(CParser& parser, CToken& target); 

	void next_char()
	{
		if( this->checkread(1) )
		{
			if( 10==*this->cScn )
			{
				++this->line;
				this->column=1;
			}
			else if( 13 != *this->cScn)
				++this->column;

			++this->cScn;
		}
	}
	short get_char()
	{
		if( this->checkread(1) )
		{
			return (*((unsigned char*)this->cScn));
		}
		else
			return  EEOF;
	}
	// get the current character from the input stream
	// to make sure that
	short get_charstep()
	{
		if( this->checkread(1) )
		{
			if( 10==*this->cScn )
			{
				++this->line;
				this->column=1;
			}
			else if( 13 != *this->cScn)
				++this->column;

			return (*((unsigned char*)this->cScn++));
		}
		else
			return  EEOF;
	}
	bool is_eof(bool reserve=true)
	{
		return !this->checkread(1);
	}
};

class CParseInputMem : public CParseInput
{
	ICL_EMPTY_COPYCONSTRUCTOR(CParseInputMem)
public:
	CParseInputMem(const char* sp, size_t sz)
		: CParseInput(sz)
	{
		this->cWpp = elaborator::intern_copy<char>(this->cBuf, sp, sz);
	}
	virtual ~CParseInputMem()
	{}
protected:
	virtual size_t readdata(char*, size_t)
	{
		return 0;
	}
};

class CParseInputFile : public CParseInput
{
	ICL_EMPTY_COPYCONSTRUCTOR(CParseInputFile)
	FILE *cFile;
public:
	CParseInputFile()
		: CParseInput(1024), cFile(NULL)
	{}
	CParseInputFile(const char* name)
		: CParseInput(1024), cFile(NULL)
	{
		this->open(name);
	}
	virtual ~CParseInputFile()
	{
		this->close();
	}
	bool open(const char* name)
	{
		this->close();
		if(name)
		{
			this->cFile = fopen(name, "rb");
			this->checkread(1);
		}
		this->init();
		return (NULL!=this->cFile);
	}
	void close()
	{
		if(this->cFile)
		{
			fclose(this->cFile);
			this->cFile=NULL;
			this->cWpp=this->cRpp=this->cScn=this->cBuf;
		}
	}
protected:
	virtual size_t readdata(char* buf, size_t sz)
	{
		return (this->cFile)?fread(buf, 1, sz,this->cFile):0;
	}
};




/*
class CParseInput : public allocator_file<char>
{
	ICL_EMPTY_COPYCONSTRUCTOR(CParseInput)
public:
	///////////////////////////////////////////////////////////////////////////
	// position marker
	unsigned int	line;
	unsigned int	column;

	CParseInput() : line(1),column(1)	{}
	virtual ~CParseInput()				{}


	bool open(const char* name)
	{
		line =1;
		column =1;
		return allocator_file<char>::open(name);
	}

	short scan(CParser& parser, CToken& target); 

	void next_char()
	{
		if( checkread(1) )
		{
			if( 10==*this->cScn )
			{
				++this->line;
				this->column=1;
			}
			else if( 13 != *this->cScn)
				++this->column;

			++this->cScn;
		}
	}
	short get_char()
	{
		if( checkread(1) )
		{
			return (*((unsigned char*)this->cScn));
		}
		else
			return  EEOF;
	}
	// get the current character from the input stream
	// to make sure that
	short get_charstep()
	{
		if( checkread(1) )
		{
			if( 10==*this->cScn )
			{
				++this->line;
				this->column=1;
			}
			else if( 13 != *this->cScn)
				++this->column;

			return (*((unsigned char*)this->cScn++));
		}
		else
			return  EEOF;
	}
	bool get_eof(bool reserve=true)
	{
		return !checkread(1);
	}
};



class CParseInput
{
	///////////////////////////////////////////////////////////////////////////
	// input buffer
	char*	buf;		// buffer
	size_t	nbufsize;	// size of the buffer
	size_t	ncount;		// number of valid characters in the buffer
	size_t	nofs;		// offset of reading char
	size_t	nbufofs;	// offset of the buffer
public:
	///////////////////////////////////////////////////////////////////////////
	// position marker
	unsigned short	line;
	unsigned short	column;

	///////////////////////////////////////////////////////////////////////////
	// user function to get input data
	//
	// This function is called when the scanner needs more data
	//
	// If the preserve flag is set(because the scanner may need to backtrack),
	// then the data in the current input buffer must be preserved.
	// This is done by increasing the buffer size and copying
	// the old data to the new buffer.
	// If the preserve flag is not set, the new data can be copied
	// over the existing buffer.
	//
	// If the input buffer is empty after this callback returns(because no
	// more data was added), the scanner function will return either:
	//   1] the last accepted token
	//   2] an eof, if no token has been accepted yet

	FILE *cFile;
	string<> cName;

	virtual void cbgetinput(bool reserve)
	{
		size_t nr;
		if( !feof(cFile) )
		{
			if( reserve )
			{	// need to keep the old content
				// copy the existing buffer to a new, larger one
				char* p = new char[2048 + this->ncount];
				this->nbufsize += 2048;
				memcpy(p, this->buf, this->ncount);
				delete[] this->buf;
				this->buf = p;
				nr = fread(this->buf+this->ncount, 1, 2048, cFile);
				this->ncount += nr; // increase the character count
			}
			else
			{	// can overwrite the old content
				nr = fread(this->buf, 1, this->nbufsize, cFile);
				this->nbufofs=this->nofs;
				//pinput.nofs = 0;					// reset the offset
				this->ncount = nr; // set the character count
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////
	// construct/destruct
	CParseInput()
		: buf(NULL),nbufsize(0),ncount(0),nofs(0),nbufofs(0),
		line(1), column(0),
		cFile(NULL)
	{
		buf = new char[2048];
		nbufsize = 2048;
	}
	virtual ~CParseInput()	{ close(); }

	///////////////////////////////////////////////////////////////////////////
	// file functions
	bool open(const char*filename)
	{
		close();
		// reset internals
		ncount=0;
		nofs=0;
		nbufofs=0;
		line=1;
		column=0;

		cFile = fopen(filename,"rb");
		if(cFile)
		{
			cName = filename;
		}
		return NULL!=cFile;
	}
	bool close()
	{
		if(cFile)
		{	
			fclose(cFile);
			cName.clear();
		}
		return NULL==cFile;
	}
	///////////////////////////////////////////////////////////////////////////
	// access functions
	// get the next token
	short scan(CParser& parser, CToken& target); 


	// increment to next character in input stream
	void next_char()
	{
		if( this->nofs < this->ncount+this->nbufofs)
			this->nofs++;

		char c = this->buf[this->nofs-this->nbufofs];
		if( c==10 )
		{
			this->line++;
			this->column=0;
		}
		else if( c!=13 )
			this->column++;
	}
	// get the next character from the input stream
	short get_char(bool reserve=true)
	{
		return this->get_eof(reserve)?EEOF:this->buf[this->nofs - this->nbufofs];
	}
	// check for eof on the input stream
	bool get_eof(bool reserve=true)
	{
		if(this->nofs >= this->ncount+this->nbufofs)
			this->cbgetinput(reserve);
		return (this->nofs >= this->ncount+this->nbufofs);
	}
};

*/


// parser configuration
class CParseConfig
{
	///////////////////////////////////////////////////////////////////////////
	friend class CParser;
public:
	///////////////////////////////////////////////////////////////////////////
	short			init_dfa;
	short			init_lalr;
	short			start_symbol;
	bool			case_sensitive;
	///////////////////////////////////////////////////////////////////////////
	//TArrayDCT< string<> >	charset;
	//TArrayDCT<CDFAState>	dfa_state;
	//TArrayDCT<CSymbol>		sym;
	//TArrayDCT<CRule>		rule;
	//TArrayDCT<CLALRState>	lalr_state;

	vector< string<> >	charset;
	vector<CDFAState>		dfa_state;
	vector<CSymbol>		sym;
	vector<CRule>			rule;
	vector<CLALRState>	lalr_state;

public:
	///////////////////////////////////////////////////////////////////////////
	CParseConfig()
		: init_dfa(0),init_lalr(0),start_symbol(0),case_sensitive(true)
	{  }
	CParseConfig(const char* filename)
		: init_dfa(0),init_lalr(0),start_symbol(0),case_sensitive(true)
	{
		if( !create(filename) ) 
			throw "";
	}
	CParseConfig(const unsigned char* buffer, size_t len)
		: init_dfa(0),init_lalr(0),start_symbol(0),case_sensitive(true)
	{ 
		if( !create(buffer, len) )
			throw "";
	}

	///////////////////////////////////////////////////////////////////////////
	// create from file
	bool create(const char* filename);
	// create from memory
	bool create(const unsigned char* buffer, size_t len);
	///////////////////////////////////////////////////////////////////////////
};


class CParser : public noncopyable
{
	ICL_EMPTY_COPYCONSTRUCTOR(CParser)
	friend class CParseInput;
public:
	bool					reduction;
	short					reduce_rule;
	short					lalr_state;

	CToken					cScanToken;
	vector<CStackElement>	cStack;
	size_t					nstackofs;
	vector<CToken>			tokens;

	CParseConfig*			pconfig;
	CParseInput*			pinput;


	// Reduction Tree
	vector<CStackElement>	rt;

	///////////////////////////////////////////////////////////////////////////
	CParser()
		: reduction(false),reduce_rule(0),lalr_state(0),
		nstackofs(0),pconfig(NULL),pinput(NULL)
	{}

	CParser(CParseConfig* pcfg)
		: reduction(false),reduce_rule(0),lalr_state(0),
		nstackofs(0),pconfig(NULL),pinput(NULL)
	{
		create(pcfg);
	}


	virtual ~CParser()
	{
		this->close();
	}

	bool open(const char *name)
	{
		this->close();
		this->pinput = new CParseInputFile(name);
		return this->pinput!=NULL && !this->pinput->is_eof();
	}
	bool open(const char *sp, size_t sz)
	{
		this->close();
		this->pinput = new CParseInputMem(sp,sz);
		return this->pinput!=NULL;
	}
	void close()
	{
		if( this->pinput )
		{
			delete this->pinput;
			this->pinput = NULL;
		}
	}


	///////////////////////////////////////////////////////////////////////////
	bool create(CParseConfig* pcfg);
	void reset();
	void reinit();

	short parse(short reduce_sym=0);

	const CStackElement* get_rt_entry(size_t idx) const;


	// Get the current lexeme
	const char*	get_lexeme() const
	{
		return this->cScanToken.cLexeme;
	}
	// Set the current rule's lexeme
	void set_lexeme(const char* lexeme)
	{
		this->cScanToken.cLexeme = lexeme;
	}


	// Get a lexeme from the stack
	const char* get_child_lexeme(int index) const
	{
		return this->cStack[this->nstackofs+index].cToken.cLexeme;
	}

	bool get_symbol(size_t syminx, CSymbol& symbol) const;


	void print_stack_element(const CStackElement& se, int indent, const char sign) const;
	void print_rt_tree(int rtpos, int indent, bool trim=true) const;
	void print_rt() const;
	void print_stack() const;
	void print_expects(const char* name=NULL) const;
	

	///////////////////////////////////////////////////////////////////////////

protected:

	bool DefaultMatchFunction(short type, const string<>& name, short symbol);
	virtual bool MatchFunction(short type, const string<>& name, short symbol);
};


class CParser_CommentStore : public CParser
{
	ICL_EMPTY_COPYCONSTRUCTOR(CParser_CommentStore)
public:
	class CLineStorage
	{
	public:
		size_t		line;
		string<>	content;
		bool		multi;

		CLineStorage()	{}
		CLineStorage(size_t l, const string<>& s, bool m=false) : line(l), content(s), multi(m)	{}

		bool operator==(const CLineStorage& a) const { return a.line==line; }
		bool operator< (const CLineStorage& a) const { return a.line< line; }
	};
	vector<CLineStorage> cCommentList;

public:
	///////////////////////////////////////////////////////////////////////////
	CParser_CommentStore()
	{}

	CParser_CommentStore(CParseConfig* pconfig)
		: CParser(pconfig)
	{}
	virtual ~CParser_CommentStore()	{}

protected:

	virtual bool MatchFunction(short type, const string<>& name, short symbol);
};












///////////////////////////////////////////////////////////////////////////
/// some simplifying interface to the parser reduction tree.
struct parse_node
{
	const CParser*			parser;
	const CStackElement*	se;
	
	parse_node() : parser(NULL), se(NULL)
	{}
	// default copy/assignment
	parse_node(const CParser& p, size_t rtpos) : parser(&p), se(&p.rt[rtpos])
	{
		advance();
	}
	parse_node(const CParser& p) : parser(&p), se(&p.rt[0])
	{
		advance();
	}
	const parse_node& advance()
	{	// truncate single node reductions
		if( this->se )
		{
			while( this->se->cChildNum==1 )
				this->se = &this->parser->rt[this->se->cChildPos];
		}
		return *this;
	}
	///////////////////////////////////////////////////////////////////////////
	// element access
	const char* c_str() const		{ return (se)? se->cToken.cLexeme.c_str():""; }
	const string<> string() const	{ return (se)? se->cToken.cLexeme.c_str():""; }
	const char*name() const			{ return (se)? se->symbol.Name.c_str():""; }
	unsigned short symbol() const	{ return (se)? se->symbol.idx :0; }
	unsigned short type() const		{ return (se)? se->symbol.Type:0; }
	size_t childs()	const			{ return (se)? se->cChildNum:0; }
	unsigned int line() const		{ return (se)? se->cToken.line:0; }
	unsigned int column() const		{ return (se)? se->cToken.column:0; }

	///////////////////////////////////////////////////////////////////////////
	// check for terminal
	bool is_terminal(int idx) const
	{
		return ( se && this->type()==1 && this->symbol()==idx );
	}
	///////////////////////////////////////////////////////////////////////////
	// check for nonterminal
	bool is_nonterminal(int idx) const
	{
		return ( se && this->type()==0 && this->symbol()==idx );
	}
	///////////////////////////////////////////////////////////////////////////
	// get a child
	parse_node operator[](size_t inx) const	{ return (se && inx<se->cChildNum)?(parse_node(*this->parser, se->cChildPos+inx)):(*this); }

	///////////////////////////////////////////////////////////////////////////
	void print(bool line_number=true, bool first=true) const
	{
		if( first && !this->type()==1 )
		{
			printf("<%s>: ", this->name());
		}
		if(first) printf("'");
		if( this->type()==1 )
		{	// terminals
			printf("%s", this->c_str());
		}
		else
		{
			size_t i;
			for(i=0; i<this->childs(); ++i)
			{
				this->operator[](i).print(false, false);
			}
		}
		if(first) printf("'");
		if(line_number)
			printf(" (line %u, column %u)", this->line(), this->column());
	}
};


NAMESPACE_END(basics)


#endif//__BASEPARSER_H__