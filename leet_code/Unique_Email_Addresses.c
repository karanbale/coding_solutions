/*

Every email consists of a local name and a domain name, separated by the @ sign.

For example, in alice@leetcode.com, alice is the local name, and leetcode.com is the domain name.

Besides lowercase letters, these emails may contain '.'s or '+'s.

If you add periods ('.') between some characters in the local name part of an email address, mail sent there will be forwarded to the same address without dots in the local name.  For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward to the same email address.  (Note that this rule does not apply for domain names.)

If you add a plus ('+') in the local name, everything after the first plus sign will be ignored. This allows certain emails to be filtered, for example m.y+name@email.com will be forwarded to my@email.com.  (Again, this rule does not apply for domain names.)

It is possible to use both of these rules at the same time.

Given a list of emails, we send one email to each address in the list.  How many different addresses actually receive mails? 

 

Example 1:

Input: ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
Output: 2
Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive mails
 

Note:

1 <= emails[i].length <= 100
1 <= emails.length <= 100
Each emails[i] contains exactly one '@' character.
All local and domain names are non-empty.
Local names do not start with a '+' character.

*/

#include "../C/standardHeaders.h"

#define ENABLE_PRINTS 1

void printf_wrapper(const char * message, ...) {
    va_list args;
    va_start(args, message);
#ifdef ENABLE_PRINTS
    vprintf(message, args);
#endif
    va_end(args);
}

int numUniqueEmails(char ** emails, int emailsSize){
    
    char retEmails[100][100]={0};
    int retEmailPtr=0;
    for(int email=0; email<emailsSize; email++){
        bool skipTillFound=false;
        bool domainNameReached=false;
        int copyPtr=0;
        char retEmailStr[100]={0};
        printf_wrapper("email val: %s\n", emails[email]);
        for(int character=0; character<strlen(*(emails+email)); character++){
            // just skip over . character
            if(((*(*(emails+email)+character)) == '.') && 
               (!domainNameReached)){
                printf_wrapper("found . skipping %c\n", (*(*(emails+email)+character)));
                continue;
            }
            // discard everything until reach @ character
            if(((*(*(emails+email)+character)) == '+') && 
               (!domainNameReached)){               
                printf_wrapper("found + skipping %c\n", (*(*(emails+email)+character)));
                skipTillFound = true;
                continue;
            }
            if((*(*(emails+email)+character)) == '@'){
                if(skipTillFound == true){
                    skipTillFound = false;
                }
                domainNameReached = true;
                printf_wrapper("%s found @ reached %c\n", retEmailStr, (*(*(emails+email)+character)));
            }
            if(skipTillFound == false){
                retEmailStr[copyPtr] = (*(*(emails+email)+character));
                //((retEmails+email)+copyPtr) = (*(*(emails+email)+character));
                copyPtr++;
            }
        }
        retEmailStr[copyPtr]='\0';
        bool emailFound=false;
        for(int checkEmail=0; checkEmail<retEmailPtr; checkEmail++){
            //printf("retEmailPtr:%d \n",retEmailPtr);
            //printf("retEmailenter   : %s\n", retEmailStr);
            //printf("retEmailexisting: %s\n", retEmails[checkEmail]);
            if(strcmp(retEmails[checkEmail], retEmailStr) == 0){
                printf_wrapper("found %s skipping it.\n\n",retEmails[checkEmail]);
                emailFound=true;
                break;
            }
            //printf("retEmailexit    : %s\n", retEmailStr);
        }
        if(!emailFound){
            printf_wrapper("adding %s to DB\n\n", retEmailStr);
            strcpy(retEmails[retEmailPtr], retEmailStr);
            retEmailPtr++;
        }
    }
    
    int retEmailCount=0;
    for(int email=0; email<emailsSize; email++){
        //printf("email: %s\n", retEmails[email]);
        if(strlen(retEmails[email]) > 0){
            retEmailCount++;
        }
        else{
            printf_wrapper("email: %s\n", retEmails[email]);
            break;
        }
    }
    printf_wrapper("ret: %d\n", retEmailCount);
    return retEmailCount;
}


int main() 
{
    char *email[100] = {"c.o.t.m.f.q+rt.i.l@zuvn.skdsq.com","d.c.fw.jc.c.gt+w@yzuq.com","n.kvtb+a.iq.c.l@rupfxkfr.com","xckqzemg+f.h@hbtp.com","mh+f.o+k.d.e.x.fe@gywxo.n.com","d.c.fw.jc.c.gt+q@yzuq.com","hh.a.fm.jea.s+t@epo.com","xckqzemg+dx@hbtp.com","n+gz.fyk+f.oi+e@j.fe.com","vqvp.p.lvt.t+k@rexcs.com","nnwhgqn+qm.n@chmgo.com","mrjrugbrh+e@z.zvnnhswsq.com","mrjrugbrh+s@z.zvnnhswsq.com","mh+fclendxh@gywxo.n.com","t.bgivgn.yh+l@sytfq.mgr.com","cv.oau.d.zsub+x@ybzkk.com","oww.sotdsb.j+w@aadoc.r.com","y.qdv+v+b+bk.di@wd.lvz.com","nnwhgqn+h.se@chmgo.com","nnwhgqn+fh.o@chmgo.com","y.m.v.l.a+f+e+o+m+u@lhn.m.com","mh+ay.gudhp+x@gywxo.n.com","bvmztjceb.l+m@uci.com","c.o.t.m.f.q+i.fy.v@zuvn.skdsq.com","w.k.uz.n.f.u+uf+l@we.mbb.com","r.s+lu.b.v.x.t.d+g@yyb.dw.com","hh.a.fm.jea.s+a@epo.com","t.bgivgn.yh+o@sytfq.mgr.com","y.qdv+z.gyuga@wd.lvz.com","mh+icx.pgzdt@gywxo.n.com","y.m.v.l.a+m.p+h+as@lhn.m.com","xckqzemg+w+k@hbtp.com","y.m.v.l.a+tt.o+h.t@lhn.m.com","n+l+mcpqdu.th@j.fe.com","w.k.uz.n.f.u+s+dg@we.mbb.com","e.pp.o.btp+g+k+v@qqnxdkht.com","q.y+epj.qb.u.vd@rq.wxd.com","u+n.p.x+zn.gv.wj@dlkmbenb.ek.com","mh+dfuaping@gywxo.n.com","mrjrugbrh+d@z.zvnnhswsq.com","d.c.fw.jc.c.gt+x@yzuq.com","n.kvtb+e+p.uu.k@rupfxkfr.com","e.pp.o.btp+ijv@qqnxdkht.com","e.pp.o.btp+mew@qqnxdkht.com","t.bgivgn.yh+x@sytfq.mgr.com","u+t.fa.f+gtp.em@dlkmbenb.ek.com","t.bgivgn.yh+u@sytfq.mgr.com","hh.a.fm.jea.s+c@epo.com","qro.hxljfov+i@pr.wlw.com","c.o.t.m.f.q+r.x.o.w@zuvn.skdsq.com","y.m.v.l.a+e.z+m.lq@lhn.m.com","y.qdv+uesdrh@wd.lvz.com","xckqzemg+t.n@hbtp.com","mh+it+kt.lc.l+r@gywxo.n.com","nnwhgqn+y.k.m@chmgo.com","n.kvtb+f.v+o.gh@rupfxkfr.com","c.o.t.m.f.q+k.uk.s@zuvn.skdsq.com","d.c.fw.jc.c.gt+d@yzuq.com","y.qdv+i.q.uikf@wd.lvz.com","mvvkycizo+w@wbs.j.com","w.k.uz.n.f.u+icw@we.mbb.com","qro.hxljfov+m@pr.wlw.com","mh+nv.m.t+p.l.a.m@gywxo.n.com","y.qdv+e.piws.f@wd.lvz.com","y.qdv+fd+fj+x.n@wd.lvz.com","n+g.f.qv.h.c.t+q.u@j.fe.com","xckqzemg+gk@hbtp.com","y.qdv+f.x.f+ptr@wd.lvz.com","vqvp.p.lvt.t+t@rexcs.com","e.pp.o.btp+hog@qqnxdkht.com","cv.oau.d.zsub+u@ybzkk.com","cv.oau.d.zsub+p@ybzkk.com","qro.hxljfov+o@pr.wlw.com","u+jaaow.ena+e@dlkmbenb.ek.com","y.m.v.l.a+m.w.egc@lhn.m.com","d.c.fw.jc.c.gt+d@yzuq.com","yj.g.wm+kn.m.v.t@aicgst.com","xckqzemg+e.g@hbtp.com","bvmztjceb.l+a@uci.com","vqvp.p.lvt.t+r@rexcs.com","qro.hxljfov+o@pr.wlw.com","y.qdv+xathpe@wd.lvz.com","mskkt+lfrso@nfxouykntm.com","mh+i.koi.hrps@gywxo.n.com","jc.g+i.jn.x.mrv@dna.f.com","w.k.uz.n.f.u+wi.u@we.mbb.com","hazmbrt.nhf+f@aztvolon.com","hh.a.fm.jea.s+t@epo.com","cv.oau.d.zsub+e@ybzkk.com","oww.sotdsb.j+t@aadoc.r.com","t.bgivgn.yh+c@sytfq.mgr.com","nnwhgqn+hhf@chmgo.com","e.pp.o.btp+apm@qqnxdkht.com","n+ipyouibnd@j.fe.com","n+y.r.ks.q.z.r.lh@j.fe.com","mrjrugbrh+r@z.zvnnhswsq.com","c.o.t.m.f.q+h.vt+r@zuvn.skdsq.com","xckqzemg+e+v@hbtp.com","c.o.t.m.f.q+o+v.e+y@zuvn.skdsq.com","q.y+un.d.d.q+n+or@rq.wxd.com"};
    printf("output: %d\n", numUniqueEmails(email, strlen(*email)));
}