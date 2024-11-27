#include <iostream>

using namespace std;

class Solution {
public:
    void dfs(string node, string& dest, unordered_map<string, unordered_map<string, double>>& gr, unordered_set<string>& vis, double& ans, double temp){
        /*string node
          string& dest
          unordered_map<string, unordered_map<string, double>>& gr
          unordered_set<string>& vis
          double& ans
          double temp
        */
        if(vis.find(node) != vis.end()) return; //si no está, lo insertamos en el mapa
        vis.insert(node);
        if(node==dest){
            ans=temp;
            return;
        }
        for(auto ne: gr[node]){  //recursión para movernos en el grafo
            dfs(ne.first, dest, gr, vis, ans, temp*ne.second);
        }
    }
    unordered_map<string, unordered_map<string, double>> buildGraph(const vector<vector<string>>& equations, const vector<double>& values){
        /*
        const vector<vector<string>>& equations
        const vector<double>& values
        */
        //aqui estaba el secreto
        unordered_map<string, unordered_map<string, double>> gr;
        for(int i=0; i<equations.size(); i++){
            string dividend=equations[i][0]; //el dividendo
            string divisor=equations[i][1]; //el divisor
            double value= values[i]; //los valores respectivos de los dos string

            gr[dividend][divisor]=value; //string, string, double
            gr[divisor][dividend]=1.0/value; //la formula incluye 0.1 para la inversa
        }
        return gr;
    }

    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, unordered_map<string, double>> gr=buildGraph(equations, values);
        vector<double> finalAns;

        for(auto query: queries){
            string dividend=query[0];
            string divisor=query[1];
            if(gr.find(dividend) == gr.end() || gr.find(divisor) == gr.end()){
                finalAns.push_back(-1.0);
            }else{
                unordered_set<string> vis;
                double ans = -1, temp=1.0;
                dfs(dividend, divisor, gr, vis, ans, temp);
                finalAns.push_back(ans);
            }
        }
        return finalAns;
    }
};

int main(){

	cout<<"hola GDIntelectual"<<endl;

	return 0;
}