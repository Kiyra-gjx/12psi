package com.zeroone.star.storemanagement.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.storemanagement.entity.ExtryDO;
import com.zeroone.star.storemanagement.mapper.OtherOutListMapper;
import com.zeroone.star.storemanagement.service.IOtherOutListService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

/**
 * 功能：
 * <p>
 * ——————————————————————————————
 * version   变更日期    修改人
 * ------------------------------
 * v1.0.0    2025/10/26    shark
 * ——————————————————————————————
 * 修改说明：
 *
 * @author: shark
 */

@Service
public class OtherOutListServiceImpl extends ServiceImpl<OtherOutListMapper, ExtryDO> implements IOtherOutListService {

    @Resource
    private OtherOutListMapper otherOutListMapper;

    @Override
    public void examine(List<Integer> ids) {
        //TODO : 待实现关联表的审核逻辑
        ExtryDO extryDO = otherOutListMapper.selectById(ids.get(0));
        if(extryDO != null) {
            update().set("examine", extryDO.getExamine() == 1 ? 0 : 1).eq("id", ids.get(0)).update();
        }
    }

    @Override
    public void check(List<Integer> ids) {
        //TODO : 待实现关联表的核对逻辑
        ExtryDO extryDO = otherOutListMapper.selectById(ids.get(0));
        if(extryDO != null) {
            update().set("`check`", extryDO.getCheck() == 1 ? 0 : 1).eq("id", ids.get(0)).update();
        }
    }
}
