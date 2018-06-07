#ifndef Xinput
#define Xinput

//‘å•¶Žš
enum padstate
{
	padon,
	padoff,
	padpush,
	padrelease
};

enum buttomindex
{
	buttomA,
	buttomB,
	buttomX,
	buttomY,
	buttomRB,
	buttomLB,
	buttomstart,
	buttomindexMAX
};

enum analog
{
	ANALOGUP,
	ANALOGDOWN,
	ANALOGLEFT,
	ANALOGRIGHT,
	ANALOGMAX
};

void Getcontrolle();
padstate Getbuttom(buttomindex index);
bool GetLanalog(analog analogstate);
void checkbuttomstate(WORD, int);

#endif