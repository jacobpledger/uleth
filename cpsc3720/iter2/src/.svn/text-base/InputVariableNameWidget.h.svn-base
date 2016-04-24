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

/*********************************************************************//**
\file
\brief Interface file for the InputVariableWidget class

\date Feb 22, 2010
\author Nathan
**********************************************************************/

#include<QHBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include<QWidget>


/*********************************************************************//**
  \brief Widget for each Input Variable

  This class provides the base dialog for receiving input from user
**********************************************************************/
class InputVariableNameWidget : public QWidget {
  
  Q_OBJECT

 public:
  ///Constructor
   InputVariableNameWidget(QWidget* parent, int n=0);
  ///Text accessor
  QString text() const { return editor->text(); }
  ///Text setter
  void setText(const QString& in) { editor->setText(in); } 
  signals:
  ///Signal emitted when text is edited
  void textEdited(const QString& text);
  private:
  QHBoxLayout* lt;
  QLabel* lbl;
  QLineEdit* editor;
};
