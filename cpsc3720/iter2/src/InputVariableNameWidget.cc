/****************************************************************************
This file is part of KMapper.

KMapper is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
KMapper is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with KMapper.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

/********************************************************************//**
\file
\brief Implementation file for the InputVariableWidget class

\date Feb 22, 2010
\author Nathan
**********************************************************************/

#include "InputVariableNameWidget.h"

InputVariableNameWidget::InputVariableNameWidget(QWidget* parent, int n):QWidget(parent){  
   lbl=new QLabel(QString("Var #%1:").arg(n+1),this);
   editor=new QLineEdit(this);
   editor->setMaxLength(2);
   editor->setMaximumWidth(50);
   editor->setInputMask(tr("AA"));
   connect(editor, SIGNAL(textEdited(const QString&)), 
	   this, SIGNAL(textEdited(const QString&)));
   lt=new QHBoxLayout();
   lt->addWidget(lbl);
   lt->addWidget(editor);
   lt->addStretch();
   this->setLayout(lt);
}
