/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/12/03 14:58:34

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "stdafx.h"
#include "Router.h"
#include "ApiHelper.h"
#include "CustomerController/CustomerController.h"
#include"FundsController/FundsController.h"
#include "GoodsController/GoodsController.h"
#include "controller/SupplierController/SupplierController.h"

#include "CustomerController/CustomerController.h"


#include "WarehouseController/WarehouseController.h"
#include "FundsController/FundsController.h"

// ��������˹ر�Swagger�ĵ���
#ifdef CLOSE_SWAGGER_DOC
// �򻯰󶨿������궨��
#define ROUTER_SIMPLE_BIND(__CLASS__) \
router->addController(__CLASS__::createShared())
#else
// �򻯰󶨿������궨��
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
	//#TIP :系统扩展路由定义，写在这个后面
	ROUTER_SIMPLE_BIND(GoodsController);
	//#TIP :ϵͳ��չ·�ɶ��壬д���������
	ROUTER_SIMPLE_BIND(SupplierController);
	// ��ʾ��������
	ROUTER_SIMPLE_BIND(WarehouseController);
	ROUTER_SIMPLE_BIND(FundsController);

	ROUTER_SIMPLE_BIND(CustomerController); //c2-快乐五香蛋
}
