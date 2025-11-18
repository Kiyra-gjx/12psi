#include "stdafx.h"
#include "Router.h"
#include "ApiHelper.h"
#include "ExamineController.h"
#include "OrderController.h"
 #include"PotableController.h"
 #include"PotableInfoController.h"
 #include"ReturnCreateController.h"
#include "ExReportDeController.h"
#include "ExReportSimController.h"
#include "PurchaseOrderJsController.h"

// 如果定义了关闭Swagger文档宏
#ifdef CLOSE_SWAGGER_DOC
#define ROUTER_SIMPLE_BIND(__CLASS__) \
router->addController(__CLASS__::createShared())
#else
// 简化绑定控制器宏定义
#define ROUTER_SIMPLE_BIND(__CLASS__) \
BIND_CONTROLLER(docEndpoints, router, __CLASS__)
#endif

Router::Router(Endpoints* docEndpoints, HttpRouter* router)
{
	this->docEndpoints = docEndpoints;
	this->router = router;
}

void Router::initRouter()
{
	ROUTER_SIMPLE_BIND(PotableController);
	ROUTER_SIMPLE_BIND(PotableInfoController);
	ROUTER_SIMPLE_BIND(ReturnCreateController);
	ROUTER_SIMPLE_BIND(ExamineController);
	ROUTER_SIMPLE_BIND(OrderController);
	ROUTER_SIMPLE_BIND(ExReportDeController);
	ROUTER_SIMPLE_BIND(ExReportSimController);
	ROUTER_SIMPLE_BIND(PurchaseOrderJsController);

}
