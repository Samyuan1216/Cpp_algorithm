#include <bits/stdc++.h>
using namespace std;

struct patient
{
    string own_name;
    string doc_name;
    int treatment = 0;
    int registration = 0;
    int check_in = 0;
    bool late = false;
    bool check = false;
};

struct doctor
{
    struct compare
    {
        bool operator()(const patient &a, const patient &b)
        {
            if (a.late != b.late)
            {
                return a.late == true;
            }

            if (a.late == true)
            {
                return a.check_in > b.check_in;
            }

            if (a.treatment == b.treatment)
            {
                return a.registration > b.registration;
            }

            return a.treatment > b.treatment;
        }
    };

    priority_queue<patient, vector<patient>, compare> heap;
};

map<string, doctor> d;
map<string, patient> p;
string s;
int T = 0, mytime = 0, hour = 0, minute = 0;

int main()
{
    cin >> T;

    while (T--)
    {
        cin >> hour >> minute >> s;
        mytime = hour * 60 + minute;

        if (s == "appointment")
        {
            string pat, doc;
            cin >> pat >> doc;

            int mh, mm, mt;
            cin >> mh >> mm;
            mt = mh * 60 + mm;

            patient p1;
            p1.own_name = pat;
            p1.doc_name = doc;
            p1.registration = mytime;
            p1.treatment = mt;

            p[pat] = p1;

            if (d.find(doc) == d.end())
            {
                doctor d1;
                d[doc] = d1;
            }
        }
        else if (s == "register")
        {
            string pat;
            cin >> pat;

            if (p.find(pat) == p.end() || mytime < p[pat].treatment - 60 || p[pat].check == true)
            {
                cout << "Fail" << endl;
            }
            else
            {
                p[pat].check = true;
                p[pat].check_in = mytime;

                if (p[pat].check_in > p[pat].treatment)
                {
                    p[pat].late = true;
                }

                d[p[pat].doc_name].heap.push(p[pat]);

                cout << "Success" << endl;
            }
        }
        else if (s == "query")
        {
            string doc;
            cin >> doc;

            if (d.find(doc) == d.end() || d[doc].heap.empty())
            {
                cout << "No patient" << endl;
            }
            else
            {
                string pat = d[doc].heap.top().own_name;
                d[doc].heap.pop();
                
                for (int i = 1; i < pat.length() - 1; i++)
                {
                    pat[i] = '*';
                }

                cout << pat << endl;
            }
        }
    }
    
    return 0;
}