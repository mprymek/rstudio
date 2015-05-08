# Created by: Ryan Steinmetz <zi@FreeBSD.org>
# $FreeBSD$

PORTNAME=	rstudio
DISTVERSION=	v0.98.1103
CATEGORIES=	devel java
MASTER_SITES+=	https://s3.amazonaws.com/rstudio-dictionaries/:dictionaries \
		https://s3.amazonaws.com/rstudio-buildtools/:buildtools \
		http://mirrors.rit.edu/zi/:DEFAULT,dictionaries,buildtools \
      https://github.com/rstudio/shinyapps/archive/:shinyapps
DISTFILES+=	${DISTVERSION}.tar.gz \
		mathjax-${JAXVER}.zip:buildtools \
		gwt-${GWTVER}.zip:buildtools \
		gin-${GINVER}.zip:buildtools \
		pandoc-${PANDOCVER}.zip:buildtools \
		core-dictionaries.zip:dictionaries \
      v${SHINYAPPSVER}.zip:shinyapps
DIST_SUBDIR=	${PORTNAME}
EXTRACT_ONLY=	${DISTVERSION}.tar.gz gwt-${GWTVER}.zip

MAINTAINER=	zi@FreeBSD.org
COMMENT=	The premier integrated development environment for R

LICENSE=	AGPLv3

EXTRACT_DEPENDS=unzip>0:${PORTSDIR}/archivers/unzip
RUN_DEPENDS=	${LOCALBASE}/bin/R:${PORTSDIR}/math/R
BUILD_DEPENDS=	${LOCALBASE}/bin/R:${PORTSDIR}/math/R \
		ant:${PORTSDIR}/devel/apache-ant
LIB_DEPENDS=	libboost_system.so:${PORTSDIR}/devel/boost-libs \
		libuuid.so:${PORTSDIR}/misc/e2fsprogs-libuuid \
		libinotify.so:${PORTSDIR}/devel/libinotify

USE_GITHUB=	yes
GH_ACCOUNT=	rstudio
GH_PROJECT=	${PORTNAME}
GH_TAGNAME=	${DISTVERSION}
GH_COMMIT=	1c6c7bd

GINVER=		1.5
GWTVER=		2.6.0
JAXVER=		23
PANDOCVER=	1.13.1
SHINYAPPSVER=	0.98.1000

#USE_GCC=	yes
USE_FORTRAN=	no
#USE_JAVA=	yes
#JAVA_BUILD=	yes
USES=		cmake:outsource
CMAKE_VERBOSE= yes
CMAKE_ARGS+=	-DRSTUDIO_TARGET=Server \
		-DCMAKE_BUILD_TYPE=Release \
		-DRSTUDIO_INSTALL_SUPPORTING=${PREFIX}/lib \
		-DRSTUDIO_INSTALL_BIN=${PREFIX}/sbin
NO_STAGE=	yes

GINFILES=	LICENSE README aopalliance.jar gin-${GINVER}-post-gwt-2.2.jar \
		gin-${GINVER}-pre-gwt-2.2.jar guice-assistedinject-snapshot.jar \
		guice-snapshot.jar javadoc javax.inject.jar
DICTIONARIES=	en_AU.aff en_AU.dic en_AU.dic_delta en_CA.aff en_CA.dic \
		en_CA.dic_delta en_GB.aff en_GB.dic en_GB.dic_delta \
		en_US.aff en_US.dic en_US.dic_delta

post-extract:
		@${MKDIR} ${WRKSRC}/src/gwt/lib/gin ${WRKSRC}/src/gwt/lib/gwt
		@${LN} -sf ${WRKDIR}/gwt-${GWTVER} ${WRKSRC}/src/gwt/lib/gwt/${GWTVER}
		@${UNZIP_CMD} -qo -d ${WRKSRC}/dependencies/common \
		   ${_DISTDIR}/mathjax-${JAXVER}.zip
		@${UNZIP_CMD} -qo -d ${WRKSRC}/dependencies/common \
		   ${_DISTDIR}/pandoc-${PANDOCVER}.zip
		@${MV} ${WRKSRC}/dependencies/common/pandoc-${PANDOCVER} \
		       ${WRKSRC}/dependencies/common/pandoc
		@${UNZIP_CMD} -qo -d ${WRKSRC}/dependencies/common \
		   ${_DISTDIR}/v${SHINYAPPSVER}.zip
		@${MV} ${WRKSRC}/dependencies/common/shinyapps-${SHINYAPPSVER} \
		       ${WRKSRC}/dependencies/common/shinyapps
		@${UNZIP_CMD} -qo -d ${WRKSRC}/dependencies/common/dictionaries \
		${_DISTDIR}/core-dictionaries.zip
		@${UNZIP_CMD} -qo -d ${WRKSRC}/src/gwt/lib/gin/${GINVER} \
		${_DISTDIR}/gin-${GINVER}.zip

.include <bsd.port.mk>
