#pragma once
#include <utility>
#include <memory>
#include "token.h"
#include "date.h"

struct Node {
    Node(const TokenType& type_ = TokenType::DATE);
    virtual bool Evaluate(const Date& d, const string& event) const = 0;
    const TokenType type;
};

struct EmptyNode : public Node {
    bool Evaluate(const Date& d, const string& event) const override;
};

struct DateComparisonNode : public Node {
    DateComparisonNode(Comparison c, Date d);
    Date rhs() const;
    Comparison comp() const;
    bool Evaluate(const Date& d, const string& event) const override;
private:
    const Comparison comp_;
    const Date rhs_;
};

struct EventComparisonNode : Node {
    EventComparisonNode(Comparison c, string rhs);
    string rhs() const;
    Comparison comp() const;
    bool Evaluate(const Date& d, const string& event) const override;
private:
    const Comparison comp_;
    const string rhs_;
};

struct LogicalOperationNode : public Node {
    LogicalOperationNode(LogicalOperation lop, shared_ptr<Node> left, shared_ptr<Node> right);
    LogicalOperation lop() const;
    std::shared_ptr<Node> left() const;
    std::shared_ptr<Node> right() const;
    bool Evaluate(const Date& d, const string& event) const override;
private:
    LogicalOperation lop_;
    std::shared_ptr<Node> left_;
    std::shared_ptr<Node> right_;
};