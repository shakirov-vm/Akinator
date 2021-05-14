
struct Knot
{
	char* data;
	struct Knot* parent;
	struct Knot* left;
	struct Knot* right;
};

class Tree
{
private:
	struct Knot* root;
public:
	Tree();
	~Tree();
	Tree& operator= (const Tree& knot);
	Tree(const Tree&) = delete;
	void FillAkinator(char* base);

	void Game();
};

struct Knot* FillKnot(struct Knot* knot, char* string, struct Knot* parent);
void KnotConstruct(struct Knot* knot, struct Knot* parent);
void DeleteBranch(struct Knot* knot);