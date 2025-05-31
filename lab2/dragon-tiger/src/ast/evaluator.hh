#pragma once

#include "nodes.hh"
#include "../utils/errors.hh"

namespace ast {

    class Evaluator : public ConstASTIntVisitor {
    public:
        virtual int32_t visit(const IntegerLiteral& node) override {
            return node.value;
        }

        virtual int32_t visit(const BinaryOperator& node) override {
            int32_t left = node.get_left().accept(*this);
            int32_t right = node.get_right().accept(*this);

            switch (node.op) {
            case o_plus: return left + right;
            case o_minus: return left - right;
            case o_times: return left * right;
            case o_divide:
                if (right == 0) utils::error(node.loc, "Division by zero");
                return left / right;
            case o_eq: return left == right ? 1 : 0;
            case o_neq: return left != right ? 1 : 0;
            case o_lt: return left < right ? 1 : 0;
            case o_le: return left <= right ? 1 : 0;
            case o_gt: return left > right ? 1 : 0;
            case o_ge: return left >= right ? 1 : 0;
            default:
                utils::error(node.loc, "Unknown binary operator");
            }
            return 0;
        }

        virtual int32_t visit(const Sequence& node) override {
            const auto& exprs = node.get_exprs();
            if (exprs.empty()) {
                utils::error(node.loc, "Empty sequence");
            }
            int32_t val = 0;
            for (auto expr : exprs) {
                val = expr->accept(*this);
            }
            return val;
        }

        virtual int32_t visit(const IfThenElse& node) override {
            int32_t cond = node.get_condition().accept(*this);
            if (cond != 0) {
                return node.get_then_part().accept(*this);
            }
            else {
                return node.get_else_part().accept(*this);
            }
        }

        virtual int32_t visit(const StringLiteral& node) override {
            utils::error(node.loc, "StringLiteral evaluation not supported");
            return 0;
        }

        virtual int32_t visit(const Let& node) override {
            utils::error(node.loc, "Let evaluation not supported");
            return 0;
        }

        virtual int32_t visit(const Identifier& node) override {
            utils::error(node.loc, "Identifier evaluation not supported");
            return 0;
        }

        virtual int32_t visit(const VarDecl& node) override {
            utils::error(node.loc, "VarDecl evaluation not supported");
            return 0;
        }

        virtual int32_t visit(const FunDecl& node) override {
            utils::error(node.loc, "FunDecl evaluation not supported");
            return 0;
        }

        virtual int32_t visit(const FunCall& node) override {
            utils::error(node.loc, "FunCall evaluation not supported");
            return 0;
        }

        virtual int32_t visit(const WhileLoop& node) override {
            utils::error(node.loc, "WhileLoop evaluation not supported");
            return 0;
        }

        virtual int32_t visit(const ForLoop& node) override {
            utils::error(node.loc, "ForLoop evaluation not supported");
            return 0;
        }

        virtual int32_t visit(const Break& node) override {
            utils::error(node.loc, "Break evaluation not supported");
            return 0;
        }

        virtual int32_t visit(const Assign& node) override {
            utils::error(node.loc, "Assign evaluation not supported");
            return 0;
        }
    };

}
