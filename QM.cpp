#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>
#include<fstream>
#include <sstream>
using namespace std;


class QM
{
public:
	int append = 0;
	int VARIABLES;
	string dontcares;
	vector<string>remainterm;
	vector<string> letterterm;
	QM(int a)//�غc�l
	{
		VARIABLES = a;
		dontcares.append(a, '-');

	}


	vector<string> getletters()
	{
		vector<string> letter;
		string letters[] = { "a","b","c","d","e","f","g","h","i","j" };
		for (int i = 0; i < this->VARIABLES; i++)
			letter.push_back(letters[i]);

		return letter;
	}

	/*�Q�i����G�i��(�λ��j)
	���+""�i�N����নstring
	*/
	string decToBin(int n)
	{
		if (n == 0)
			return n + "";

		if (n % 2 == 0)
			return decToBin(n / 2) + "0";
		else
			return decToBin(n / 2) + "1";
	}

	//��0
	//�|��: �|�ܼƪ�2, 10 -> 0010
	string pad(string bin)
	{
		int max = VARIABLES - bin.length();
		for (int i = 0; i < max; i++)
			bin = "0" + bin;
		return bin;
	}

	//�ˬd�ⶵ�O�_�i�X��
	bool checkmerge(string a, string b)
	{
		int onlyonechance = 0;
		for (int i = 0; i < a.length(); i++)
		{
			if (a[i] != b[i])
				onlyonechance++;
		}
		return (onlyonechance == 1);//�u�t1��1�Nreturn true
	}

	//�[ '-'
	// Eg:0110 0111 �ܦ�011-
	string replace_complements(string a, string b)
	{
		string dash = "";
		for (int i = 0; i < a.length(); i++)
			if (a[i] != b[i])
				dash = dash + "-";
			else
				dash = dash + a[i];


		return dash;
	}

	//�ˬd�O�_�i��term��i�hvector
	bool in_vector(vector<string> a, string b)
	{
		for (int i = 0; i < a.size(); i++)
			if (a[i].compare(b) == 0)
				return true;
		return false;
	}

	int fuck = 1;
	int shit = 1;
	int chegg = 0;
	//�}�l��²�o
	vector<string> reduce(vector<string> minterms)
	{
		static int  num = 1;
		vector<string> newminterms;
		vector<string> newnum;
		
		int max = minterms.size();
		int* checked = new int[max];
		int totalsum = 0;
		for (int i = 0; i < max; i++)
		{


			for (int j = i; j < max; j++)
			{


				if (checkmerge(minterms[i], minterms[j]))
				{
					checked[i] = 1;
					checked[j] = 1;
					newminterms.push_back(replace_complements(minterms[i], minterms[j]));

					newnum.push_back(bin_to_dec(minterms[i]) + ',' + bin_to_dec(minterms[j]));//to be continued
					if (fuck == 1) {
						letterterm.push_back(bin_to_dec(minterms[i]) + ',' + bin_to_dec(minterms[j]));
					}
					else if (fuck == 2)
					{
						if (i < letterterm.size() && j < letterterm.size())
						{
							letterterm[totalsum] = letterterm[i] + ',' + letterterm[j];

							totalsum++;
						}
					}


				}

			}
		}
		fuck++;
		if (num % 2 == 1) {
			cout << "===========================" << endl;
			static int sum = 2;

			cout << "Column " << sum << endl;
			cout << "===========================" << endl;
			cout << endl;
			sum++;
		}
		int jump = 1;//����
		if (num % 2 == 1) {
			for (int i = 0; i < newminterms.size(); i++)
			{
				if (newminterms[i].find("1", 0) != -1 && jump == 1)
				{
					cout << "---------------------------" << endl;
					jump = 0;
					
				}
				cout << "v " << newminterms[i] << " : ";
				if (shit == 1)cout << newnum[i] << endl;
				else
					cout << letterterm[i] << endl;

			}
			shit = 0;
		}
		//�[�Ѿl��


		for (int i = 0; i < minterms.size(); i++)
		{


			if (checked[i] != 1 && !in_vector(newminterms, minterms[i]))
			{
				newminterms.push_back(minterms[i]);
			
				if (chegg == 0) {
					
					remainterm.push_back(bin_to_dec(minterms[i]));  //�Ĥ@���S�Q�è쪺�N��O�Ѿl���A���s�_��
					
				}
			}
		}
		chegg = 1;

		for (int i = 0; i < minterms.size(); i++)
		{


			if (checked[i] != 1 && !in_vector(newminterms, minterms[i])) {
				
			
			}
		}
		num++;
		delete[] checked;



		return newminterms;
	}
	//�G�i����Q�i��
	string bin_to_dec(string minterms)
	{
		int Dec = 0;
		int c = 1;
		for (int i = 0; i < minterms.size(); i++)
		{
			if (minterms.at(i) == '-')
			{
				minterms.at(i) = '1';
			}
		}
		int n = atoi(minterms.data());//��string�ন���
		while (n > 0)
		{
			Dec += (n % 10)*c;
			c = c * 2;
			n /= 10;
		}
		stringstream ss;//int��string
		ss << Dec;
		string result;
		ss >> result;
		return result;
	}

	//�ন�r���Φ�
	// Eg: 011->a'bc
	string getValue(string a)
	{

		string temp = "";
		vector<string> abc = this->getletters();
		if (a == dontcares)
			return "1";

		for (int i = 0; i < a.length(); i++)
		{
			if (a[i] != '-')
			{
				if (a[i] == '0')
					temp = temp + abc[i] + "\'";
				else
					temp = temp + abc[i];
			}
		}

		return temp;
	}

	//�ˬd��vector�O�_�۵�,(�j��פ����)
	bool VectorsEqual(vector<string> a, vector<string> b)
	{
		if (a.size() != b.size())
			return false;

		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] != b[i])
				return false;
		}
		return true;
	}

};



//�D�{��
int main()
{
	ifstream readfile("input.txt", ios::in);
	if (!readfile) {
		cerr << "Failed opening" << endl;
		exit(1);

	}
	ofstream outfile("output.txt", ios::out);
	if (!outfile) {
		cerr << "Failed opening" << endl;
		exit(1);
	}

	int variable;
	char trash;
	readfile >> trash;//�M��{
	readfile >> variable;//�Y�ivariable
	readfile >> trash;//�M��}
	QM QQQ(variable);
	string temp = "";
	readfile >> trash;//�M��{

	vector<string> minterms;

	string s;
	vector<int>mintermsnum;
	int yes[10] = { 0 };
	//ŪMinterm

	while (readfile >> temp)
	{
		istringstream f(temp);
		getline(f, s, ',');


		int t = atoi(s.data());//��string�ন���
		minterms.push_back(QQQ.pad(QQQ.decToBin(t)));//��G�i���A���vector��
		mintermsnum.push_back(t);//�s���
		if (temp.find("}", 0) != -1)//Ū��"}"�Nbreak
		{
			break;
		}
	}
	int minnum = minterms.size();
	//Ūdontcare
	string dontcare;
	readfile >> trash;//�M��{


	while (readfile >> dontcare)//��dontcare����1
	{
		istringstream dont(dontcare);
		getline(dont, s, ',');
		int t = atoi(s.data());//��string�ন���
		minterms.push_back(QQQ.pad(QQQ.decToBin(t)));//��G�i���A���vector��
		mintermsnum.push_back(t);
	}
	cout << "===========================" << endl;
	cout << "Column 1" << endl;
	cout << "===========================" << endl;

	int total[1024] = { 0 };
	for (int i = 0; i < minterms.size(); i++)
	{
		for (int j = 0; j < variable; j++)
			total[i] += minterms[i].at(j) - '0';

	}

	for (int i = 0; i < minterms.size(); i++)
	{

		if (total[i] == 0)
		{
			if (i < minnum) {
				cout << "v " << minterms[i] << " : " << mintermsnum[i] << endl;
				yes[0] = 1;
			}
			else if (i >= minnum) {
				cout << "d " << minterms[i] << " : " << mintermsnum[i] << endl;

			}
		}

	}
	if (yes[0] == 1)
		cout << "--------------------------" << endl;
	for (int i = 0; i < minterms.size(); i++)
	{

		if (total[i] == 1)
		{
			if (i < minnum) {
				cout << "v " << minterms[i] << " : " << mintermsnum[i] << endl;
				yes[1] = 1;
			}
			else if (i >= minnum) {
				cout << "d " << minterms[i] << " : " << mintermsnum[i] << endl;

			}
		}

	}
	if (yes[1] == 1)
		cout << "--------------------------" << endl;
	for (int i = 0; i < minterms.size(); i++)
	{

		if (total[i] == 2)
		{
			if (i < minnum) {
				cout << "v " << minterms[i] << " : " << mintermsnum[i] << endl;
				yes[2] = 1;
			}
			else if (i >= minnum) {
				cout << "d " << minterms[i] << " : " << mintermsnum[i] << endl;

			}
		}

	}
	if (yes[2] == 1)
		cout << "--------------------------" << endl;
	for (int i = 0; i < minterms.size(); i++)
	{

		if (total[i] == 3)
		{
			if (i < minnum) {
				cout << "v " << minterms[i] << " : " << mintermsnum[i] << endl;
				yes[3] = 1;
			}
			else if (i >= minnum) {
				cout << "d " << minterms[i] << " : " << mintermsnum[i] << endl;

			}
		}

	}
	if (yes[3] == 1)
		cout << "--------------------------" << endl;
	for (int i = 0; i < minterms.size(); i++)
	{

		if (total[i] == 4)
		{
			if (i < minnum) {
				cout << "v " << minterms[i] << " : " << mintermsnum[i] << endl;
				yes[4] = 1;
			}
			else if (i >= minnum) {
				cout << "d " << minterms[i] << " : " << mintermsnum[i] << endl;

			}
		}

	}
	if (yes[4] == 1)
		cout << "--------------------------" << endl;
	for (int i = 0; i < minterms.size(); i++)
	{

		if (total[i] == 5)
		{
			if (i < minnum) {
				cout << "v " << minterms[i] << " : " << mintermsnum[i] << endl;
				yes[5] = 1;
			}
			else if (i >= minnum) {
				cout << "d " << minterms[i] << " : " << mintermsnum[i] << endl;

			}

		}

	}
	if (yes[5] == 1)
		cout << "--------------------------" << endl;
	for (int i = 0; i < minterms.size(); i++)
	{

		if (total[i] == 6)
		{
			if (i < minnum) {
				cout << "v " << minterms[i] << " : " << mintermsnum[i] << endl;
				yes[6] = 1;
			}
			else if (i >= minnum) {
				cout << "d " << minterms[i] << " : " << mintermsnum[i] << endl;

			}
		}

	}
	if (yes[6] == 1)
		cout << "--------------------------" << endl;
	for (int i = 0; i < minterms.size(); i++)
	{

		if (total[i] == 7)
		{
			if (i < minnum) {
				cout << "v " << minterms[i] << " : " << mintermsnum[i] << endl;
				yes[7] = 1;
			}
			else if (i >= minnum) {
				cout << "d " << minterms[i] << " : " << mintermsnum[i] << endl;

			}
		}

	}
	if (yes[7] == 1)
		cout << "--------------------------" << endl;
	for (int i = 0; i < minterms.size(); i++)
	{

		if (total[i] == 8)
		{
			if (i < minnum) {
				cout << "v " << minterms[i] << " : " << mintermsnum[i] << endl;
				yes[8] = 1;
			}
			else if (i >= minnum) {
				cout << "d " << minterms[i] << " : " << mintermsnum[i] << endl;

			}
		}

	}
	if (yes[8] == 1)
		cout << "--------------------------" << endl;
	for (int i = 0; i < minterms.size(); i++)
	{

		if (total[i] == 9)
		{
			yes[9] = 1;
			if (i < minnum) {
				cout << "v " << minterms[i] << " : " << mintermsnum[i] << endl;
				yes[9] = 1;
			}
			else if (i >= minnum) {
				cout << "d " << minterms[i] << " : " << mintermsnum[i] << endl;

			}
		}
	}
	if (yes[9] == 1)
		cout << "--------------------------" << endl;
	for (int i = 0; i < minterms.size(); i++)
	{

		if (total[i] == 10)
		{
			if (i < minnum) {
				cout << "v " << minterms[i] << " : " << mintermsnum[i] << endl;
				yes[0] = 1;
			}
			else if (i >= minnum) {
				cout << "d " << minterms[i] << " : " << mintermsnum[i] << endl;

			}
		}

	}
	cout << endl;

	cout << endl;
	sort(minterms.begin(), minterms.end()); //�Ѥp��j�Ƨ�





	while (1) {
		minterms = QQQ.reduce(minterms);
		//sort(minterms.begin(), minterms.end());
		if (QQQ.VectorsEqual(minterms, QQQ.reduce(minterms)))
		{
			break;
		}
	}

	//for (int i = 0; i < QQQ.letterterm.size(); i++)
	//	cout << QQQ.letterterm[i]<<endl;
	
	vector <vector<int> >number(QQQ.letterterm.size());
	
	vector<string> shit(QQQ.letterterm.size());
	//��letterterm���ƫ�s�_�ӨӤ�����O�_�ۦP
	for (int i = 0; i < QQQ.letterterm.size(); i++) {
	
		stringstream ss(QQQ.letterterm[i]);
	
		while (true)
		{
			getline(ss, shit[i], ',');
			if (ss.fail())
			{
				break;
			}
			number[i].push_back(atoi(shit[i].data()));
			
		}
	}
	vector<string>final;//�s�̫᪺minterm�Ʀr
	for (int i = 0; i < number.size(); i++) {
		sort(number[i].begin(), number[i].end()); //�Ѥp��j�Ƨ�	(�~�i�H���)
	}
	for (int i = 0; i < number.size(); i++) {
		for (int j = i+1; j < number[i].size(); j++)
		{
			if (j < number[i].size())
			{
				if (number[i] == number[j])
				{
					final.push_back(QQQ.letterterm[i]);//�L�o�����ƶ�
				}
			}
		}
	}
	vector<vector<int>> finalnum(final.size());
	for (int i = 0; i < final.size(); i++) {

		stringstream ss(final[i]);
		string damn;
		while (true)
		{
			getline(ss,damn,',');
			if (ss.fail())
			{

				break;
			}
			finalnum[i].push_back(atoi(damn.data()));
			
		}
	}
	   
	

	
//�C�X�Ҧ���minterm
	
	for (int i = 0; i < final.size(); i++)
	{
		cout << minterms[i] << " ";
		cout << " " << final[i] << endl;
	}
	cout << endl;
	cout << "============================================================================================"<<endl;
	cout << "Result" << endl;
	cout << "============================================================================================" << endl;

	cout << "                    | ";
	
	vector<int>endgame;
	//endgame�Y�iremainterm���Ʀr
	for (int i = 0; i < QQQ.remainterm.size(); i++) {
	
		stringstream ss(QQQ.remainterm[i]);
		string damn;
		while (true)
		{
			getline(ss, damn, ',');
			if (ss.fail())
			{

				break;
			}
			endgame.push_back(atoi(damn.data()));

		}
	}
	//endgame�Y�i�X�ֶ����Ʀr
	for (int i = 0; i < finalnum.size(); i++)
	{
		for (int j = 0; j < finalnum[i].size(); j++)
		{
			endgame.push_back(finalnum[i][j]);
		}
	}
	
	sort(endgame.begin(), endgame.end()); //�Ѥp��j�Ƨ�
	for (int i = 0; i < endgame.size(); i++)
	{
		for (int j = i + 1; j < endgame.size(); j++)//�R�����ƥX�{���Ʀr
		{
			if (j + 1 < endgame.size()) {
				if (endgame[i] == endgame[j])
				{
					endgame.erase(endgame.begin()+j);
				}
			}
		}
	}

	for (int i = 0; i < endgame.size(); i++)
	{
		cout << setw(6) <<endgame[i] << ",";
	}

	cout << endl;
	cout << "--------------------+-------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < minterms.size(); i++)
		cout  << setw(20) <<left<<QQQ.getValue(minterms[i])<<"|"<<endl;//�����׶}�h1��+
	cout << "--------------------+-------------------------------------------------------------------------------" << endl;
	cout << endl;



	int i;

	if (variable == 8)
		cout << "F(A,B,C,D,E,F,G,H)=";
	else if (variable == 9)
		cout << "F(A,B,C,D,E,F,G,H,I)=";
	else
		cout << "F(A,B,C,D,E,F,G,H,I,J)=";

	for (i = 0; i < minterms.size() - 1; i++)
		cout << QQQ.getValue(minterms[i]) << "+";//�����׶}�h1��+

	cout << QQQ.getValue(minterms[i]) << endl;


	system("pause");
}