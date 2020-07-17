Name:           myutils
Version:        0.0.1
Release:        0
Summary:        my utils

License:        GPL
URL:            http://localhost/
Source0:        dummy.tar.gz

BuildRequires:  rpmdevtools
Requires:       rpm

%description
my utils


%prep
%setup -DTn .


%build


%install
install -D bin/cf $RPM_BUILD_ROOT/usr/local/bin/cf


%files
/usr/local/bin/cf
%doc



%changelog
