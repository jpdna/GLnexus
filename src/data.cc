#include <assert.h>
#include "data.h"

using namespace std;

namespace GLnexus {

struct DataCache::body {
    Data* data;
    vector<pair<string,size_t> > contigs;
};

DataCache::DataCache() = default;
DataCache::~DataCache() = default;

Status DataCache::Start(Data* data, unique_ptr<DataCache>& ptr) {
    ptr.reset(new DataCache);
    ptr->body_.reset(new DataCache::body);
    ptr->body_->data = data;
    return ptr->body_->data->contigs(ptr->body_->contigs);
}

Status DataCache::contigs(vector<pair<string,size_t> >& ans) const {
    ans = body_->contigs;
    return Status::OK();
}

Status DataCache::sampleset_samples(const string& sampleset, shared_ptr<const set<string> >& ans) const {
    // TODO cache
    return body_->data->sampleset_samples(sampleset, ans);
}

Status DataCache::sample_dataset(const string& sample, string& ans) const {
    // TODO cache
    return body_->data->sample_dataset(sample, ans);
}

Status DataCache::dataset_bcf_header(const string& dataset, shared_ptr<const bcf_hdr_t>& hdr) const {
    // TODO cache
    return body_->data->dataset_bcf_header(dataset, hdr);
}

Status DataCache::dataset_bcf(const string& dataset, const bcf_hdr_t* hdr, const range& pos, vector<shared_ptr<bcf1_t> >& records) const {
    return body_->data->dataset_bcf(dataset, hdr, pos, records);
}

Status DataCache::dataset_bcf(const string& dataset, const range& pos, shared_ptr<const bcf_hdr_t>& hdr, vector<shared_ptr<bcf1_t> >& records) const {
    Status s;
    S(dataset_bcf_header(dataset, hdr));
    return dataset_bcf(dataset, hdr.get(), pos, records);
}

const vector<pair<string,size_t> >& DataCache::contigs() const {
    return body_->contigs;
}

Status DataCache::sampleset_datasets(const string& sampleset,
                                     shared_ptr<const set<string>>& samples,
                                     shared_ptr<const set<string>>& datasets_out) const {
    // TODO cache
    Status s;
    auto datasets = make_shared<set<string>>();
    S(sampleset_samples(sampleset, samples));
    for (const auto& it : *samples) {
        string dataset;
        S(sample_dataset(it, dataset));
        datasets->insert(dataset);
    }
    datasets_out = datasets;
    return Status::OK();
}

}
