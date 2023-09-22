/*******************************************************************************
 * Copyright IBM Corp. and others 2019
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution
 * and is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following Secondary
 * Licenses when the conditions for such availability set forth in the
 * Eclipse Public License, v. 2.0 are satisfied: GNU General Public License,
 * version 2 with the GNU Classpath Exception [1] and GNU General Public
 * License, version 2 with the OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] https://openjdk.org/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0-only WITH Classpath-exception-2.0 OR GPL-2.0-only WITH OpenJDK-assembly-exception-1.0
 *******************************************************************************/

#ifndef GENERICNODECONVERTER_HPP
#define GENERICNODECONVERTER_HPP

#include "converter.hpp"

namespace Tril {

class ASTToTRNode;

class GenericNodeConverter: public ASTToTRNode {
    public:
        /**
         * @brief Constructs an instance of Tril::GenericNodeConverter
         * @param next is the next object that gets a chance to convert the AST node if the current on fails
         */
        explicit GenericNodeConverter(ASTToTRNode* next = NULL) : ASTToTRNode(next) {}

    protected:
        /**
         * @brief Generates the TR::Node for AST structure based on the opcode type
         * @param tree the AST structure
         * @param state the object that encapsulating the IL generator state
         * @return TR::Node represented by the AST 
         */
        TR::Node* impl(const ASTNode* tree, IlGenState* state); /* override */
};

class GenericNodeGenError : public ILGenError {
    public:
	    explicit GenericNodeGenError(std::string message): ILGenError(message) {}
};

}
#endif
