#define MAX_DATA_SIZE 100
#define MAX_BASE_SIZE 100000

struct Node
{
	char* data;
	struct Node* parent;
	struct Node* left;
	struct Node* right;
};

class Tree
{
private:
	struct Node* root;
public:
	Tree();
	~Tree();
	Tree& operator= (const Tree& node) = delete;
	Tree(const Tree&) = delete;
	void LoadBase(char* base);
	void DumpGraph();
	void Play();
	void Game();
	void DumpBase();
};

struct Node* ChargeNode(struct Node* node, char* string, struct Node* parent);
void NodeConstruct(struct Node* node, struct Node* parent);
void DeleteBranch(struct Node* node);
void NodePrint(struct Node* node, FILE* potok); 
