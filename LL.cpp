#include "LL.h"


LL::LL()
{
  
  table_analyse.clear();
  grammar.clear();
  kind.clear();
  first.clear();
  follow.clear();
  select.clear();
  pos = 0;
  character.clear();
  //"S->E" "E->Ta" "T->p"
  /*
  E -> T Z ① {I,(}
  Z-> a T Z ② {a }|ε ③{),#}
  T -> F P ④ {I,(}
  P-> b F P ⑤{b}|ε⑥{a,),#}
  F -> i ⑦{I} | ( E ) ⑧{(}
  */

  /*
  //E->aZ|b
  //Z->aE
  character.push_back("E");//0
  character.push_back("Z");//1
  character.push_back("a");//2
  character.push_back("b");//3
  character.push_back("#");//4
  kind.push_back(1);
  kind.push_back(1);

  kind.push_back(0);
  kind.push_back(0);
  kind.push_back(0);
  vector<int> temp_grammar;
  temp_grammar.push_back(0);
  temp_grammar.push_back(2);

  temp_grammar.push_back(1);
  grammar.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(0);
  temp_grammar.push_back(3);
  grammar.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(1);
  temp_grammar.push_back(2);
  temp_grammar.push_back(0);
  grammar.push_back(temp_grammar);
  */
  line.push_back("i");
  line.push_back("b");
  line.push_back("i");
  line.push_back("#");
  
  character.push_back("E");//0
  character.push_back("T");//1
  character.push_back("Z");//2
  character.push_back("F");//3
  character.push_back("P");//4
  character.push_back("a");//5
  character.push_back("b");//6
  character.push_back("(");//7
  character.push_back(")");//8
  character.push_back("i");//9
  character.push_back("$");//10
  character.push_back("#");//11
  kind.push_back(1);
  kind.push_back(1);
  kind.push_back(1);
  kind.push_back(1);
  kind.push_back(1);
  kind.push_back(0);
  kind.push_back(0);
  kind.push_back(0);
  kind.push_back(0);
  kind.push_back(0);
  kind.push_back(0);
  kind.push_back(0);
  vector<int> temp_grammar;
  temp_grammar.push_back(0);
  temp_grammar.push_back(1);
  temp_grammar.push_back(2);
  grammar.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(2);
  temp_grammar.push_back(5);
  temp_grammar.push_back(1);
  temp_grammar.push_back(2);
  grammar.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(2);
  temp_grammar.push_back(10);
  grammar.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(1);
  temp_grammar.push_back(3);
  temp_grammar.push_back(4);
  grammar.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(4);
  temp_grammar.push_back(6);
  temp_grammar.push_back(3);
  temp_grammar.push_back(4);
  grammar.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(4);
  temp_grammar.push_back(10);
  grammar.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(3);
  temp_grammar.push_back(9);
  grammar.push_back(temp_grammar);
  temp_grammar.clear();
  temp_grammar.push_back(3);
  temp_grammar.push_back(7);
  temp_grammar.push_back(0);
  temp_grammar.push_back(8);
  grammar.push_back(temp_grammar);

 
  follow[0].push_back(11);

  

  for (int i = 0; i < (int)character.size(); ++i)
  {
    if (first[i].empty())
    {
      if (kind[i] == 0) // 终极符的first等于本身
        first[i].push_back(i);
      else
      {
        make_first(i);
      }
    }
  }
  
  make_follow(0);
  
  for (int i = 1; i < (int)character.size(); ++i)
  {
    if(follow[i].empty())
      make_follow(i);

  }
  /*
  
  */
  for (int i = 0; i < (int)character.size() - 1; ++i)
  {
    cout << character[i] << "\t";
    for (int j = 0; j < (int)follow[i].size(); ++j)
    {
      cout << follow[i][j] << " ";
    }
    cout << endl;
  }
  table_make();
  //select 没有删除空和重复
  for (int i = 0; i < (int)select.size(); ++i)
  {
    cout << i << " ";
    for (int j = 0; j < (int)select[i].size(); ++j)
    {
      cout << character[select[i][j]] << " ";
    }
    cout << endl;
  }
  
  cout << "\t";
  for (int i = 0; i < (int)character.size(); ++i)
  {
    if (kind[i] == 0)
    {
      cout << character[i] << "\t";
    }
  }
  cout << endl;
  for (int i = 0; i < (int)character.size(); ++i)
  {

    if (kind[i] == 1)
    {

      cout << character[i] << "\t";
      for (int j = 0; j < (int)character.size(); ++j)
      {
        if (kind[j] == 0)
        {
          index temp;
          temp.state = character[i];
          temp.V = character[j];
          cout << table_analyse[temp] << "\t";
        }
      }
      cout << endl;
    }

  }
 
  if (action() == 1)
    cout << "yes";
  else cout << "no";
}

int LL::action()
{
  int i;
  for ( i = 0; i < (int)character.size(); ++i)
  {
    if (character[i] == "#")
      break;
  }
  stack_state.push(i);
  stack_state.push(0);
    while (character[stack_state.top()] != "#" || line[pos] != "#")
  {
    if (kind[stack_state.top()] == 0/*栈顶是终结符*/ && line[pos] == character[stack_state.top()])
    {
      stack_state.pop();
      pos++;
    }
    else if (kind[stack_state.top()] == 1)
    {
      index temp;
      temp.state = character[stack_state.top()];
      temp.V = line[pos];
      if (table_analyse[temp] != -1)
      {
        stack_state.pop();
        for (int i = (int)grammar[table_analyse[temp]].size() - 1; i >= 1; --i)
        { // 逆序压栈
          
          if (character[grammar[table_analyse[temp]][i]] != "$")
          {
            stack_state.push(grammar[table_analyse[temp]][i]);
          }
         
           
          
        }
       
      }
      else
      {
        //返回错误
        cout << temp.state <<" "<< temp.V<<"1"<<endl;
        return 0;
      }
    }
    else
    {
      cout << character[stack_state.top()] << " " << line[pos]<< "2"<<endl;
      //返回错误
      return 0;
    }
  }
    return 1;
}

void LL::table_make()
{
  for (int i = 0; i < (int)grammar.size(); ++i)
  {
    //select 集合的构建
    //这是一个VECTOR 里面是first集合；
    int flag = 0;
    int j;
    int p = 1;
    while (p < (int)grammar[i].size())
    {
      
      flag = 0;
      for (j = 0; j < (int)first[grammar[i][p]].size(); ++j)
      {
        //判断第i个文法的产生式右边第一个的first集合中是否存在空
        if (character[first[grammar[i][p]][j]] == "$")
        {
          
          flag = 1; // 有空的信号
          break;
        }
      }
      if (flag == 1)
      {
        
        for (int k = 0; k < (int)first[grammar[i][p]].size(); ++k)
        {
          if (character[first[grammar[i][p]][k]] == "$")
            continue;
          int flag1 = 0;
          for (int m = 0; m < (int)select[i].size(); ++m)
          {
            if (select[i][m] == first[grammar[i][p]][k])
            {
              flag1 = 1;
              break;
            }
          }
          if (flag1 == 0)
            select[i].push_back(first[grammar[i][p]][k]);
        }
        p++;
      }
      else
      {
        for (int k = 0; k < (int)first[grammar[i][p]].size(); ++k)
        {
          int flag1 = 0;
          for (int m = 0; m < (int)select[i].size(); ++m)
          {
            if (select[i][m] == first[grammar[i][p]][k])
            {
              flag1 = 1;
              break;
            }
          }
          if (flag1 == 0)
            select[i].push_back(first[grammar[i][p]][k]);
        }
        break;
      }
    }
    if (p == (int)grammar[i].size())
    {
     
      for (int k = 0; k < (int)follow[grammar[i][0]].size(); ++k)
      {
        int flag1 = 0;
        for (int m = 0; m < (int)select[i].size(); ++m)
        {
          if (select[i][m] == follow[grammar[i][0]][k])
          {
            flag1 = 1;
            break;
          }
        }
        if (flag1 == 0)
          select[i].push_back(follow[grammar[i][0]][k]);
      }
    }
    
  }

  for (int i = 0; i < (int)character.size(); ++i)
  {
    
    index temp;
    temp.state = character[i];
    for (int j = 0; j < (int)character.size(); ++j)
    {
      if (kind[j] == 0)
      {
        temp.V = character[j];
        table_analyse[temp] = -1;
        
      }
    }
  }


  for (int i = 0; i < (int)select.size(); ++i)
  {
    index temp;
    temp.state = character[grammar[i][0]];
    for (int j = 0; j < (int)select[i].size(); ++j)
    {
      temp.V = character[select[i][j]];
      table_analyse[temp] = i;
    }
    
  }
}



void LL::make_first(int index)
{
  for (int j = 0; j < (int)grammar.size(); ++j)
  {
    if (grammar[j][0] == index)
    {

      if (kind[grammar[j][1]] == 0)
      {
        int flag = 0;
        for (int k = 0; k <(int) first[index].size(); ++k)
        {
          if (first[index][k] == grammar[j][1])
          {
            flag = 1;
            break;
          }

        }
        if (flag == 0)
          first[index].push_back(grammar[j][1]);
      }
      else
      {
        if (empty(first[grammar[j][1]]))
        {
          make_first(grammar[j][1]);
        }
        for (int k = 0; k < (int)first[grammar[j][1]].size(); ++k)
        {
          int flag = 0;
          for (int m = 0; m <(int) first[index].size(); ++m)
          {
            if (first[index][m] == grammar[j][1])
            {
              flag = 1;
              break;
            }

          }
          if (flag == 0)
            first[index].push_back(first[grammar[j][1]][k]);

        }

      }
    }
  }
}


void LL::make_follow(int index)
{
  for (int i = 0; i < (int)grammar.size(); ++i)
  {
    for (int j = 1; j < (int)grammar[i].size(); ++j)
    {
      
      if (grammar[i][j] == index)
      {
        int p = j+1;
        
        int flag = 1;
        while (p < (int)grammar[i].size() )
        {
          
          flag = 0;
          for (int k = 0; k < (int)first[grammar[i][p]].size(); ++k)
          {
            if (character[first[grammar[i][p]][k]] == "$") // first集合中存在空
            {
             
              flag = 1;
              break;
            }
          }
          if (flag == 0)
          {
            join(follow[index], first[grammar[i][p]]);
            break;
          }
          else
          {
            // first集合中存在空
            join(follow[index], first[grammar[i][p]]);
            
            p++;
           
          }
          
        }
        if (p == (int)grammar[i].size()  && flag == 1 && p != index)
        {
          //如果该符号后是空，那么插入follow[grammar[i][0]]
          //cout << index << " "<< grammar[i][0];

          //消除间接follow递归
          //E->aEZ|b
          //Z->aE
          
          

          if (follow[grammar[i][0]].empty() && grammar[i][0] != index)
          {
           
            make_follow(grammar[i][0]);
          }
          
          join(follow[index], follow[grammar[i][0]]);
        }
      }
    }
  }
}

void LL::join(vector<int> &f1, vector<int> f2)
{
  for (int i = 0; i < (int)f2.size(); ++i)
  {
    int flag = 0;
    for (int j = 0; j < (int)f1.size(); ++j)
    {
      if (f2[i] == f1[j])
      {
        flag = 1;
        break;
      }
    }
    if (flag == 0 && character[f2[i]] != "$")
    {
      f1.push_back(f2[i]);
    }
  }
}