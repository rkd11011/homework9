/*
 * Binary Search Tree #1
 * 이진 탐색 트리
 * 자료구조 9번째 과제
 * 충북대학교 2017015040 물리학과 강수
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {//노드
	int key;//값
	struct node *left;//왼쪽 자식
	struct node *right;//오른쪽 자식
} Node;

int initializeBST(Node** h);//초기화 함수

void inorderTraversal(Node* ptr);	  //재귀 inorder 순회 출력
void preorderTraversal(Node* ptr);    //재귀 preorder 순회 출력
void postorderTraversal(Node* ptr);	  //재귀 postorder 순회 출력
int insert(Node* head, int key);  //노드추가

int deleteLeafNode(Node* head, int key);  //리프노드 판단후 삭제
Node* searchRecursive(Node* ptr, int key);  //재귀노드 탐색 후 해당노드 주소반환
Node* searchIterative(Node* head, int key);  //반복 노드탐색 후 해당 노드주소 반환
int freeBST(Node* head); //모든 메모리해제

int main()
{
	char command;//명령 분류에 사용
	int key;//키값 받는데 사용
	Node* head = NULL; //헤드 노드
	Node* ptr = NULL;//임시 저장소

    printf("[----- [kang su] [2017015040] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//명령어 입력

		switch(command) {//명령어 처리
		case 'z': case 'Z':
			initializeBST(&head);//초기화
			break;
		case 'q': case 'Q':
			freeBST(head);//메모리 전부 해지
			break;
		case 'n': case 'N'://노드추가
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);//노드추가
			break;
		case 'd': case 'D'://해당 노드 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);//리프노드 삭제
			break;
		case 'f': case 'F'://
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);//재귀를 사용하지 않고 헤드노드와 키값으로 노드탐색후 해당노드주소를 반환
			if(ptr != NULL)//해당노드가 있는경우
				printf("\n node [%d] found at %p\n", ptr->key, ptr);//찾은노드 출력
			else
				printf("\n Cannot find the node [%d]\n", key);//해당노드가 없는경우 출력
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);//루트노드와 키값으로 재귀로 노드탐색 하고 해당 주소를 반환
			if(ptr != NULL)//해당노드가 있는경우
				printf("\n node [%d] found at %p\n", ptr->key, ptr);//찾은노드 출력
			else
				printf("\n Cannot find the node [%d]\n", key);//해당노드가 없는경우 출력
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);//첫노드부터 시작 출력
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);//첫노드부터 시작 출력
			break;
		case 't': case 'T':
			postorderTraversal(head->left);//첫노드부터 시작 출력
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

    //만일 기존노드가 있으면 기존노드 해지
	if(*h != NULL)//기존노드가 있으면
		freeBST(*h);//노드해지

	//헤드노드 생성
	*h = (Node*)malloc(sizeof(Node));//메모리 할당
	(*h)->left = NULL;	//루트노드 위치
	(*h)->right = *h;
	(*h)->key = -9999;
    //printf("[%p] ",*h);
	return 1;
}



void inorderTraversal(Node* ptr)
{
    //첫노드 부터시작
    //왼쪽노드 있습니까?네-왼쪽노드 재귀호출,아니오-?
    //[자신출력]
    //오른쪽노드 있습니까?네-오른쪽노드 재귀호출,아니오-?

    //첫 노드 부터 시작
   
    if(ptr!=NULL){//노드가 있는경우
        if(ptr->left){ //왼쪽이 있을 경우
            inorderTraversal(ptr->left);//왼쪽 주소로 재귀호출
        } 
        
        printf("[%d] ",ptr->key);//자신 값 출력
        //printf("[%d /Lp: %p /Rp: %p] ",ptr->key,ptr->left,ptr->right);
        
        if(ptr->right){//오른쪽 노드가 있을 경우
            inorderTraversal(ptr->right);//오른쪽 주소로 재귀호출
        } 
    
    }else printf("Nothing to print.\n");//노드가 없는경우
   
}

void preorderTraversal(Node* ptr)
{
    //첫노드 부터시작
    //[자신출력]
    //왼쪽노드 있습니까?네-왼쪽노드 재귀호출,아니오-?
    //오른쪽노드 있습니까?네-오른쪽노드 재귀호출,아니오-?

    //첫 노드 부터 시작
   
    if(ptr!=NULL){//노드가 있는경우

        printf("[%d] ",ptr->key);//자신 값 출력
        //printf("[%d /Lp: %p /Rp: %p\n] ",ptr->key,ptr->left,ptr->right);

        if(ptr->left){ //왼쪽이 있을 경우
            preorderTraversal(ptr->left);//왼쪽 주소로 재귀호출
        } 
          
        if(ptr->right){//오른쪽 노드가 있을 경우
            preorderTraversal(ptr->right);//오른쪽 주소로 재귀호출
        } 
    
    }else printf("Nothing to print.\n");//노드가 없는경우


}

void postorderTraversal(Node* ptr)
{
    //첫노드 부터시작
    //왼쪽노드 있습니까?네-왼쪽노드 재귀호출,아니오-?
    //오른쪽노드 있습니까?네-오른쪽노드 재귀호출,아니오-?
    //[자신출력]

    
    //첫 노드 부터 시작
   
    if(ptr!=NULL){//노드가 있는경우


        if(ptr->left){ //왼쪽이 있을 경우
            postorderTraversal(ptr->left);//왼쪽 주소로 재귀호출
        } 
          
        if(ptr->right){//오른쪽 노드가 있을 경우
            postorderTraversal(ptr->right);//오른쪽 주소로 재귀호출
        } 

        printf("[%d] ",ptr->key);//자신 값 출력
        //printf("[%d /Lp: %p /Rp: %p\n] ",ptr->key,ptr->left,ptr->right);
    
    }else printf("Nothing to print.\n");//노드가 없는경우
    

}


int insert(Node* head, int key)
{
    Node* node = (Node*)malloc(sizeof(Node));//노드생성
    node->key = key;//노드에 값저장
    node->left=NULL;
    node->right=NULL;

	if(head->left==NULL){//노드가 없을경우
        head->left=node;
     
		return 0;// 종료
	}

	//이미 노드가 있을 경우
    Node* n = head->left;//루트노드 부터시작
    Node* perv = NULL;//이전 노드를 기록
    while (n!=NULL) {//이동한 장소 값이 널 일경우
        perv=n;
        if(key<n->key){//새 값이 비교노드 보다 작을 때
            n=n->left;
        }else{//새 값이 비교노드 보다 클 때
            n=n->right;
        }
    }
    if(key<perv->key){//새 값이 비교노드보다 작을 때
        perv->left=node;
    }else{//그외 새 값이 비교노드보다 크거나 같을 때 
        perv->right=node;    
    }

    

	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {//초기화전
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {//등록된 노드가 없는경우
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	//처음노드
	Node* ptr = head->left;


	//자식노드로 이동하기 위해 부모노드도 기억해야한다
	Node* parentNode = head;

	while(ptr != NULL) {//노드가 NULL이 아닐때까지

		if(ptr->key == key) {//노드의 값이 입력한 값과 같은경우
			if(ptr->left == NULL && ptr->right == NULL) {//자식노드가 없는경우

				if(parentNode == head)//부모노드가 헤드노드인 경우
					head->left = NULL;//헤드노드에 루트노드가 없음을 알린다.

				if(parentNode->left == ptr)//부모의 왼쪽이 삭제된경우
					parentNode->left = NULL;//부모의 왼쪽이 삭제됨을 알림
				else//그외 부모의 오른쪽 노드가 삭제됨
					parentNode->right = NULL;//부모의 오른쪽이 삭제됨을 알림

				free(ptr);//해당노드 메모리 해지
			}
			else {//리프노드가 아닌경우
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		parentNode = ptr;//자식을 부모로 두고 해당노드 아래를 탐색한다

		if(ptr->key < key)//입력 값과 노드를 비교 입력한 키값이 노드보다 큰 경우
			ptr = ptr->right;// 오른쪽 자식으로 이동
		else//입력한 키값이 노드보다 작은경우
			ptr = ptr->left;// 왼쪽 자식으로 이동
	}
	//리프노드 까지탐색했는데 같은 노드가 없는경우
	printf("Cannot find the node for key [%d]\n ", key);

	return 1;


}

Node* searchRecursive(Node* ptr, int key)//재귀 탐색
{
	if(ptr == NULL)//대상노드가 없는경우
		return NULL;

	if(ptr->key < key)//입력된 값이 노드값보다 큰 경우
		ptr = searchRecursive(ptr->right, key);//오른쪽자식으로 이동 재귀
	else if(ptr->key > key)//입력된 값이 노드값보다 작은경우
		ptr = searchRecursive(ptr->left, key);//왼족으로 이동 재귀

	//키값이 같은경우
	return ptr;
}

Node* searchIterative(Node* head, int key)//반복탐색
{
	Node* ptr = head->left;//루트노드

	while(ptr != NULL)//노드가 없을 때까지 반복
	{
		if(ptr->key == key)//입력된 값과 노드값이 같은 경우
			return ptr;//현노드 위치 반환

		if(ptr->key < key) ptr = ptr->right;//키값이 노드값보다 큰경우 오른쪽지식으로 이동
		else//키값이 노드값보다 작은경우
			ptr = ptr->left;//왼족자식으로 이동
	}

	return NULL;//해당 노드가 없음을 알림
}

void freeNode(Node* ptr)//노드 해지용 재귀호출 사용
{
	if(ptr) {//포인터가 있을경우
		freeNode(ptr->left);//왼쪽 노드 해지예약 재귀
		freeNode(ptr->right);//오른쪽 노드 해지예약 재귀
		free(ptr);//현노드 해지
	}
}


int freeBST(Node* head)//전체노드 해지
{
	if(head->left == NULL)//루트노드가 없는경우
	{
		free(head);//헤드노드만 해지
		return 1;
	}

	Node* p = head->left;//처음노드

	freeNode(p);//노드들 재귀로 해지

	free(head);//헤드포인터 해지
	return 1;
}




