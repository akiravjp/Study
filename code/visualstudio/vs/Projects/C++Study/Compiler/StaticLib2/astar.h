#ifndef __ASTAR_H__
#define __ASTAR_H__

#include <vector>
#include <memory>
#include <cstdint>
#include <functional>
//#include "KVector2.h"
//#include "CoreMath.h"
#include "KVector2.h"

class BlockAllocator;

class AStar
{
public:
    typedef std::function<bool(const KVec2&)> Callback;

    /**
     * ��������
     */
    struct Params
    {
        bool        corner;     // ����ս�
        uint16_t    height;     // ��ͼ�߶�
        uint16_t    width;      // ��ͼ���
        KVec2       start;      // �������
        KVec2       end;        // �յ�����
        Callback    can_pass;   // �Ƿ��ͨ��

        Params() : height(0), width(0), corner(false)
        {
        }
    };

    struct STest
    {
        int a;
        int b;
    };
    struct SSubTest : public STest
    {

    };

public:
    /**
     * ·���ڵ�״̬
     */
    enum NodeState
    {
        NOTEXIST = 0,               // ������
        IN_OPENLIST,            // �ڿ����б�
        IN_CLOSEDLIST           // �ڹر��б�
    };

    /**
     * ·���ڵ�
     */
    struct Node
    {
        uint16_t    g;          // ��������
        uint16_t    h;          // ���յ����
        KVec2 pos;        // �ڵ�λ��
        NodeState   state;      // �ڵ�״̬
        Node*       parent;     // ���ڵ�

        /**
         * ����fֵ
         */
        int f() const
        {
            return g + h;
        }

        inline Node(const KVec2 &pos)
            : g(0), h(0), pos(pos), parent(nullptr), state(NOTEXIST)
        {
        }
    };

public:
    AStar(BlockAllocator *allocator);

    ~AStar();

public:
    /**
     * ��ȡֱ�й�ֵ
     */
    int get_step_value() const;

    /**
     * ��ȡ�սǹ�ֵ
     */
    int get_oblique_value() const;

    /**
     * ����ֱ�й�ֵ
     */
    void set_step_value(int value);

    /**
     * ��ȡ�սǹ�ֵ
     */
    void set_oblique_value(int value);

    /**
     * ִ��Ѱ·����
     */
    std::vector<KVec2> find(const Params& param);
    void find(Params& param, std::vector<KVec2> vecPath);
    //void test(STest& a);
    //void test4(SSubTest& a);
    //void test1(Params& a);
    //void test2(std::vector<int> vecTest);
    //void test3(std::vector<KVECTOR2> vecTest);
    //void test5(KVec2& v2Test);
    //void test6(std::vector<SSubTest> vecTest);
    ////void test7(KVec2Test& vec2Test);
    ////void test8(std::vector<KVec2Test> vecTest);
    //void test9(std::vector<KVec2> vecTest);
private:
    /**
     * �������
     */
    void clear();

    /**
     * ��ʼ������
     */
    void init(const Params &param);

    /**
     * �����Ƿ���Ч
     */
    bool is_vlid_params(const Params &param);

private:
    /**
     * ���������
     */
    void percolate_up(size_t hole);

    /**
     * ��ȡ�ڵ�����
     */
    bool get_node_index(Node *node, size_t *index);

    /**
     * ����Gֵ
     */
    uint16_t calcul_g_value(Node *parent, const KVec2&current);

    /**
     * ����Fֵ
     */
    uint16_t calcul_h_value(const KVec2&current, const KVec2&end);

    /**
     * �ڵ��Ƿ�����ڿ����б�
     */
    bool in_open_list(const KVec2&pos, Node *&out_node);

    /**
     * �ڵ��Ƿ�����ڹر��б�
     */
    bool in_closed_list(const KVec2&pos);

    /**
     * �Ƿ��ͨ��
     */
    bool can_pass(const KVec2 &pos);

    /**
     * ��ǰ���Ƿ�ɵ���Ŀ���
     */
    bool can_pass(const KVec2 &current, const KVec2 &destination, bool allow_corner);

    /**
     * ���Ҹ�����ͨ���Ľڵ�
     */
    void find_can_pass_nodes(const KVec2 &current, bool allow_corner, std::vector<KVec2> *out_lists);

    /**
     * �����ҵ��ڵ�����
     */
    void handle_found_node(Node *current, Node *destination);

    /**
     * ����δ�ҵ��ڵ�����
     */
    void handle_not_found_node(Node *current, Node *destination, const KVec2 &end);

private:
    int                     step_val_;
    int                     oblique_val_;
    std::vector<Node*>      mapping_;
    uint16_t                height_;
    uint16_t                width_;
    Callback                can_pass_;
    std::vector<Node*>      open_list_;
    BlockAllocator*         allocator_;
};

#endif
