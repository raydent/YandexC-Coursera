#include "node.h"


Node::Node(const TokenType& type_) : type(type_) {};
DateComparisonNode::DateComparisonNode(Comparison c, Date d) : Node(TokenType::COMPARE_OP), comp_(c), rhs_(d) {};
EventComparisonNode::EventComparisonNode(Comparison c, string rhs) : Node(TokenType::COMPARE_OP), rhs_(rhs), comp_(c) {};
LogicalOperationNode::LogicalOperationNode(LogicalOperation lop, std::shared_ptr<Node> left, std::shared_ptr<Node> right) : Node(TokenType::LOGICAL_OP), left_(left), right_(right), lop_(lop) {};


Date DateComparisonNode::rhs() const { return rhs_; };
string EventComparisonNode::rhs() const { return rhs_; };
Comparison DateComparisonNode::comp() const { return comp_; };
Comparison EventComparisonNode::comp() const { return comp_; };
LogicalOperation LogicalOperationNode::lop() const { return lop_; };
std::shared_ptr<Node> LogicalOperationNode::left() const { return left_; };
std::shared_ptr<Node> LogicalOperationNode::right() const { return right_; };

bool EmptyNode::Evaluate(const Date& d, const string& event) const {
    return true;
}

bool DateComparisonNode::Evaluate(const Date& lhs, const string& event) const {
    switch (comp()) {
    case(Comparison::Equal):
        return lhs == rhs();
        break;
    case(Comparison::Greater):
        return rhs() < lhs;
        break;
    case(Comparison::GreaterOrEqual):
        return rhs() < lhs || rhs() == lhs;
        break;
    case(Comparison::Less):
        return (lhs < rhs());
        break;
    case(Comparison::LessOrEqual):
        return lhs < rhs() || lhs == rhs();
        break;
    case(Comparison::NotEqual):
        return (lhs < rhs()) || (rhs() < lhs);
        break;
    }
    return false;
}

bool EventComparisonNode::Evaluate(const Date& date, const string& lhs) const {
    switch (comp()) {
    case(Comparison::Equal):
        return lhs == rhs();
        break;
    case(Comparison::Greater):
        return rhs() < lhs;
        break;
    case(Comparison::GreaterOrEqual):
        return rhs() < lhs || rhs() == lhs;
        break;
    case(Comparison::Less):
        return (lhs < rhs());
        break;
    case(Comparison::LessOrEqual):
        return lhs < rhs() || lhs == rhs();
        break;
    case(Comparison::NotEqual):
        return (lhs < rhs()) || (rhs() < lhs);
        break;
    }
    return false;
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& lhs) const {
    switch (lop()) {
    case(LogicalOperation::And):
        return left()->Evaluate(date, lhs) && right()->Evaluate(date, lhs);
        break;
    case(LogicalOperation::Or):
        return left()->Evaluate(date, lhs) || right()->Evaluate(date, lhs);
        break;
    }
    return false;
}