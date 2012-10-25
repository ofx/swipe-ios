svn status | perl -ne 's/^\?\s+(\S.+)$/\1/g;chomp;system("svn add \"$_\"");'
